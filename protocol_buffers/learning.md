# Protocol Buffers 笔记

| proto文件消息类型 | C++类型 | 说明 |
| --------------- | ------ | ---- |
| double | double | |
| float | float | |
| int32 | int32 | 使用可变长编码方式, 负数时不够高效, 应该使用sint32 |
| int64 | int64 | 同上 |
| uint32 | uint32 | 使用可变长编码方式 |
| uint64 | uint64 | 同上 |
| sint32 | int32 | 使用可变长编码方式, 有符号的整型值, 负数编码时比通常的int32更高效 |
| sint64 | sint64 | 同上 |
| fixed32 | uint32 | 总是4个字节, 如果数值总是比2^28大的话, 这个类型会比uint32高效 |
| fixed64 | uint64 | 总是8个字节, 如果数值总是比2^56大的话, 这个类型会比uint64高效 |
| sfixed32 | int32 | 总是4个字节 |
| sfixed64 | int64 | 总是8个字节 |
| bool | bool | |
| string | string | 一个字符串, 必须是utf-8或者是7-bit的ASCII编码的文本 |
| bytes | string | 可能包含任意顺序的字节数据 |

+ varints 编码
+ zig zag
+ Tag Length Value

## 面对小数值的高效率序列化方案:varints和zigzag编码

> 序列化是在传输数据的时候非常重要的一环, 而对于如何高效的序列化数字一直是人们非常关心的问题, 在历史的长河中也有很多的工程师提出了有效的序列化方案, 这篇文章就讲一下在protobuf中使用到的两种数字序列化编码方案: **varints**和**zigzag**

------

### varints

**可变长**编码方案, 用于把整数进行**序列化**, 在序列化一些大概率比较小的整数的时候效率会好一些.

我们传输时使用的是一个字节流, 也就是由byte组成的bytes. 我们在各个语言中声明的整数都是有固定的大小的: 比如说四个字节大小. 但是如果一些数字本身的取值范围就很小, 那么在序列化时就会产生很多的浪费, 因为前几个字节位很可能都是由0组成的. 因此varints就是为了能够在序列化整数时能够有更好的效率而产生的一种编码方式.

varints将每一个字节(8-bit)中的第一bit抽出用于标识是否还有后续字节, 剩余7-bit用来表示内容, 而在组合的时候则是逆序组合, 就像下面这样:

十进制: ``2019`` -> 二进制: ``111 11100011``

假设这个数字是使用``golang``中的``uint``类型存储的, 那么它应该占用了内存中``32-bit``的空间, 也就是``4``个字节:

```
    byte4      byte3      byte2      byte1
╭──────────┬──────────┬──────────┬──────────╮
│ 00000000 │ 00000000 │ 00000111 │ 11100011 │
╰──────────┴──────────┴──────────┴──────────╯
```

我们在传输的时候真的太难受了: 白白浪费了两个字节的空间! 那么我们使用``varints``来进行一下编码吧! 或许会更好一些!

首先第一步, 把原来的串按照``7-bit``拆分, 舍去多余的前导0:

```
111 11100011 -> 0001111 1100011
```

然后第二步, 把所有的``7-bit``片逆序排列:

```
 byte2   byte1      byte1   byte2
0001111 1100011 -> 1100011 0001111
```

然后在每个非结尾``7-bit``片前面加上``1``, 在最后一个``7-bit``片前加上``0``:

```
╭───┬─────────╮╭───┬─────────╮   ╭───┬─────────╮╭───┬─────────╮
│   │ 1100011 ││   │ 0001111 │ ->│ 1 │ 1100011 ││ 0 │ 0001111 │ 
╰───┴─────────╯╰───┴─────────╯   ╰───┴─────────╯╰───┴─────────╯
```

而最后我们得到了两个``8-bit``字节: 我们可以用它来进行传输啦! 而且我们省去了两个字节!

大家一定可以发现一些使用``varints``的限制和缺陷:

+ 首先, varints会把数字表示的最大范围缩小, 比如uint使用varints就只能表示2^28, 这是因为极端情况缺少了4个标志位.
+ 其次, 在一个变量频繁的大于2^22次方时, 我们编码后也不会节省任何的空间, (为了不失真甚至还有可能变大), 因此varints编码只适用于相对较小的数字的序列化.
+ 如果序列化的数字对象为负数, 则和上一种情况类似, 不会有任何空间的节省. 因为符号位在最前会被视为很大的一个数.

但是在面对**较小的数字**的时候, ``varints``的效果是非常显著的.

------

### zig zag

zig zag是将有符号数统一映射到无符号数的一种编码方式, 从结果来看可以看出其名字的由来: 0, -1, 1, -2, 2 编码后变为了 0, 1, 2, 3, 4. 负数和正数以绝对值不断增大的方式来回在数轴上跳跃穿插.也就是zig zag.

我们从极端情况来看zig zag的解决方案: -1:

```
 1 -> 00000000 00000000 00000000 00000001
-1 -> 11111111 11111111 11111111 11111111
```

对于1而言, 无论是zig zag还是varints都会相对而言觉得很好处理, 因为传输时的主要思想就是对于前导0的省略, 而对于负数的补码而言, 有大量的前导1出现在字节中, 这就导致了编码上的困难.

是什么导致了这种情况呢? 一是因为**符号位放在最前**, 二是因为负数**取补码**时将大量的0都变成了1.

对于第一个原因, 工程师们决定把符号位重新编码放到最后, 而对于第二个原因, 工程师们决定对于负数把除了符号位以外的位都反转过来. 而对于正数则不变(除了将符号位也放在最后)

```
                                             符号位
zig_zag(1): 00000000 00000000 00000000 0000001_0
zig_zag(-1):00000000 00000000 00000000 0000000_1
```

所以就出现了像我们一开头提到的情况: 正数和负数来来回回的映射到正数数轴上.

我们可以使用C++简单的位运算来实现``zig zag``:

```cpp
int zigzag(int num) {
    return (num << 1) ^ (n >> 31); 
}
```

``varints``将无用的字节省略掉, ``zig zag``则解决了负数的问题, 但是这二者在面对绝对值较大的数字时都是非常无力的, 因此在应用时应当分清不同的场景, 仅有在序列化绝对值较小的数字时才会使用这两种编码方式.

### 编码规范的演化与TLV

看了一些晚上的资料, 顺便了解了一下历史上编码规范的制定历史:

#### 一, 紧凑时代

> 时代背景是刚刚有类似DOS的时候, 这个时候的显著特征就是各方面都很原始, 带宽很低, 因此在传输数据的时候要省之又省, 因此协议的编码规范以紧凑为特点.

假设武大和华师要搞一个数据传输协议, 目的是传输一本书的信息, 然后两个学校商量好了:

```c
struct BookInfo {
    unsigned short cmd; // 代表不同的操作
    char[8]  num;
    char[60] name;
}
```

学校觉得应该是可以的, 这个协议可以很好的沟通数据了! 也非常的节省空间!

```
+---+---+----+
|cmd|num|name|
+---+---+----+
| 2 | 8 | 60 |
+---+---+----+
```

这种编码规范的特点就是紧凑, 对于空间的利用率高, 导致这样的特征出现是因为当时的时代环境所限制, 带宽是非常珍贵的, 因此能省则省, 不允许冗余字段的产生.

#### 二, Version的出现

在两三年后, 武大想在这个数据传输协议中增加一个字段: 入馆日期. 我们可以叫它``date``, 然后我们的结构体可以这样去写:

```c
struct BookInfo {
    unsigned short cmd; // 代表不同的操作
    char[8] num;
    char[60] name;
    char[8] date; // 日期存储的形式为: 19990101这种
}
```

嗯, 这样安排应该也挺紧凑的, 但是问题很快就凸显了出来: 接收方无法判断应该按照旧的方式去解析数据帧还是按照新的方式去解析数据帧, 因为不可能一夜之间所有的服务都按照新的编码规范来传输数据. 因此一个叫做版本号的字段就这样诞生了:

```c
struct BookInfo {
    char version; // 版本字段, 用于标识当前的版本号
    unsigned short cmd;
    char[8] num;
    char[60] name;
    char[8] date;
}
```

```
+-------+---+---+----+----+
|version|cmd|num|name|date|
+-------+---+---+----+----+
|   1   | 2 | 8 | 60 | 4  |
+-------+---+---+----+----+
```

这样根据版本号就可以使用不同的解析方式, 也就解决了之前的问题, 在这里其实版本号就是一个冗余的字段, 但是由于这个字段本身占用的空间不大, 而且当时的带宽已经比之前宽松了一点. 这样的方式现在还有不少协议都在使用.

#### 三. Tag的出现

虽然有了版本号能够让我们在协议的构建的时候能够拥有一定的可扩展性, 但是一个协议仅有一个冗余字段来维护还是略显单薄了一些: 当我们拥有很多个版本的协议的时候, 意味着我们的代码里将会出现相当多的``case``, 然后我们的代码就会变得非常的臃肿, 所以我们尝试加入更多的冗余信息: ``tag``.

``tag``的作用是用来标识一个字段的解析方式, 一个特定的``tag``可以用于标识一个字段, 这个字段的解析方式完全可以通过``tag``来判断, 解析数据帧的时候就可以通过遇见的``tag``来解析接下来一个或几个字节的数据. 这样就可以拥有更好的可扩展性:

```
+-------+---+---+---+---+---+----+---+----+
|version|tag|cmd|tag|num|tag|name|tag|date|
+-------+---+---+---+---+---+----+---+----+
|   1   | 1 | 2 | 1 | 8 | 1 | 60 | 1 | 4  |
+-------+---+---+---+---+---+----+---+----+
```

#### 四, TLV和TTLV

**1. TLV**

在使用了Tag之后, 我们程序的可扩展性好了很多, 但是有时候会出现这样的情况: 我们的书名可能只占4个或者5个字节, 但是仍然分配了60个字节的空间, 这显然有点浪费吧! 所以人们就想着加上后续的长度这类冗余信息会不会让协议变得更加高效?

好在这种形式早在[ASN.1](https://baike.baidu.com/item/ASN.1/498523)中的BER(Basic Encoding Rule)中提出了:

> BER的数据由三个域组成: 标识域(tag), 长度域(length)和值域(value), 又叫做TLV

也就是说, 一个数据段由三个部分组成:

```
+---+------+-----+
|tag|length|value|
+---+------+-----+
```

``tag``的作用是用于标识字段是什么, ``length``用于告知解析程序后续的值域的字节长度, ``value``用于存储真正的数据.

而且TLV的模式还可以嵌套使用.

这样的TLV其实已经够棒了, 对吗? 因为我们已经牺牲了足够多的冗余空间来帮助我们达成数据传输协议的高可扩展性, 当数据传输中不定长的字段比较多的时候这样往往是很有效的, 但是如果字段都是占用空间比较小的时候(比如说字符和一些数值), TLV并没有很大的提升整体解析的效率. 并且TLV这样一种模式不具有**自解释性**.

> 所谓自解释性, 是指可以通过阅读代码或者数据包本身来知晓其结构和特征, 而不需要依靠特定的文档来实现.

比如我们希望随便抓一个数据包, 就能知道每个字段的键, 类型等等信息.

**2. TTLV**

所谓的TTLV, 是指**Tag, Type, Length, Value**, 在这其中加上了Type, 就能够在数据中直接知晓一个数据段的数据类型, 相应的, 在一些确定长度的类型下, 我们还可以删减掉长度这个辅助信息[所以其实是**TT(L)V**], 这样接收方就能够只看数据包而知晓数据传输协议的编码规范.

比如我们定义了几个类型: ``int8``用``1``表示, ``int32``用``2``表示, ``string``用``3``表示, 这样的话``int8``和``int32``的值域其实是定长的, 而只有``string``类型的字段是需要长度域的, 比如:

```go
type Info struct {
    One   int8
    Two   int32
    Three string
}
```

这样一个Go语言中的结构体, 如果我们传输他的话, 按照TTLV的形式, 数据帧的编码规范应该是这样的:

```
+---+----+-----+---+----+-----+---+----+------+-----+
|tag|type|value|tag|type|value|tag|type|length|value|
+---+----+-----+---+----+-----+---+----+------+-----+
|   | 1  |1-bit|   | 2  |4-bit|   | 3  |  x   |x-bit|
+---+----+-----+---+----+-----+---+----+------+-----+
```

编码规范的演化, 一方面受着**物理环境因素的影响(指带宽)**, 另一方面受**人类需求**的影响, 所以在使用TLV或者TTLV之前一定要了解整个编码规范的历史进程, 这样才能更好的理解为什么会出现TLV和TTLV.

## 使用protobuf的步骤:

### 安装protoc:

首先我们要在本地把protoc的源码克隆下来:

    git clone https://github.com/protocolbuffers/protobuf.git

然后把我们需要使用的命令都安装一下:

    sudo apt-get install autoconf automake libtool curl make g++ unzip

然后我们进入目录下开始安装:

    cd protobuf
    git submodule update --init --recursive
    ./autogen.sh
    ./configure
    make
    make check
    sudo make install
    sudo ldconfig

然后再使用终端输入``protoc``这个命令就可以使用了

### 写好proto文件

