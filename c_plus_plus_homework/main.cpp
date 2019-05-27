#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>

using namespace std;

int ppt_page_count = 0;


class Graph {
public:
    int type;
    // type == 1: triangle
    // type == 2: rectangle
    // type == 3: round
    // type == .. ...
    // type == 0: undefined
    int line_color;
    int fill_color;
    int line_width;

    Graph() {
        this->type = 0;
        this->line_color = 0x000000;
        this->fill_color = 0x000000;
        this->line_width = 0;
        // color is RGB is (0-255, 0-255, 0-255)
    }
    virtual void Save(fstream & file) = 0;
    virtual void Open(fstream & file) = 0;
    virtual void Display() = 0;
};

class TextBox: public Graph {
public:
    int width;
    int height;
    int left;
    int top;
    // the width, height, left, top set the text box's position.
    // 0---------> left
    // |
    // |
    // |
    // \/
    // top
    char text_string[101];
    // the text_string is the content of text box

    void Save(fstream & file) {};
    void Open(fstream & file) {};
    void Display() {
        cout << "\t\t[Display]: -*- TextBox: " << this->text_string << " -*-" << endl;
        cout << "\t\t\t| Width : " << this->width << endl;
        cout << "\t\t\t| Height: " << this->height << endl;
        cout << "\t\t\t| Left  : " << this->left << endl;
        cout << "\t\t\t| Top   : " << this->top << endl;
        cout << "\t\t\t| Line Color : " << this->line_color << endl;
        cout << "\t\t\t| Fill Color : " << this->fill_color << endl;
        cout << "\t\t\t| Line Width : " << this->line_width << endl;
    };
};

class PPTPage {
private:
    int pageNum;
    char logo[50]; // bit map or icon
    vector<TextBox *> text_boxes;
public:
    PPTPage() {
        // constructor
    }

    void AddTextBox(TextBox * text_box) {
        this->text_boxes.push_back(text_box);
        return;
    }

    void SetPageNum(int page_num) {
        this->pageNum = page_num;
        return;
    }

    int GetPageNum() {
        return this->pageNum;
    }

    void Display() {
        cout << "\t[Display]: -*- Page: " << this->pageNum << " -*-" << endl;
        for (auto iter: this->text_boxes) {
            (*iter).Display();
        }
        return;
    }
};

PPTPage * ppt_page_buffer; // buffer for copy and paste

class CDocument {
private:
    vector<PPTPage *> pptpages;
public:
    char name[101];

    CDocument() {
        strcpy(this->name, "undefined.myppt");
    }

    int Pages() {
        return this->pptpages.size();
    }

    void AddPage() {
        PPTPage * p = new PPTPage();
        p->SetPageNum(ppt_page_count);
        ppt_page_count += 1;
        this->pptpages.push_back(p);
    }

    PPTPage * Index(int i) {
        if (i < this->Pages()) {
            return this->pptpages[i];
        }
        return nullptr;
    }

    void Save() {
        ofstream fout(this->name, ios_base::out|ios_base::app|ios_base::binary);
        if (!fout.is_open()) {
            cout << "[Save]: Open PPT file failed." << endl;
            return ;
        } else {
            fout.write((char*)this, sizeof(CDocument));
            fout.flush();
            fout.close();
        }
        cout << "[Save]: Save the PPT successfully!" << endl;
        return ;
    }

    void Display() {
        cout << "[Display]: -*- PPT: " << this->name << " -*-" << endl;
        for (auto iter: this->pptpages) {
            if (iter == nullptr) {
                cout << "\t[Display][Error]Page is Nullptr." << endl;
            }
            (*iter).Display();
        }
        return ;
    }

    void Copy() {
        return ;
    }

    void Paste(PPTPage * new_page) {
        static PPTPage page = *new_page;
        this->pptpages.push_back(&page);
        return ;
    }

    void Cut(int index) {
        if (index < this->Pages()) {
            ppt_page_buffer = this->Index(index);
            this->Delete(index);
        } else {
            cout << "[Cut]: The index out of range." << endl;
        }
        cout << "[Cut]: Cut successfully." << endl;
        return ;
    }

    void Delete(int index) {
        if (index < this->Pages()) {
            this->pptpages.erase(this->pptpages.begin() + index);
        } else {
            cout << "[Delete]: The index out of range." << endl;
        }
        return ;
    }

    void Insert(int index, PPTPage * new_page) {
        if (index < this->Pages()) {
            static PPTPage page = *new_page;
            this->pptpages.insert(this->pptpages.begin() + index, &page);
        } else {
            cout << "[Insert]: Index out of range." << endl;
            return;
        }
        cout << "[Insert]: Insert successfully." << endl;
        return ;
    }
};


CDocument * create_cdocment() {
    cout << "Start create a new PPT." << endl;

    CDocument * doc = new CDocument;
    cout << "[Create]: Please input the PPT file name: ";
    cin >> doc->name;
    cout << "[Create]: Create new PPT named *" << doc->name << "* successfully." << endl;
    return doc;
}

void save_cdocment(CDocument * doc) {
    cout << "Start to save a PPT." << endl;

    if (doc == nullptr) {
        cout << "[Save]: Can't save the nullptr. Please open or create new PPT at first." << endl;
        return;
    }
    doc->Save();
    return;
}

CDocument * open_cdocment() {
    cout << "Start to open a PPT." << endl;

    static CDocument doc;
    char file_name[100];
    cout << "[Open]: Input the file name: ";
    cin >> file_name;
    ifstream fin;
    fin.open(file_name, ios_base::in|ios_base::binary);

    if(fin.is_open()) {
        if (fin.read((char*)&doc, sizeof(CDocument))) {
            try {
                cout << "[Open]: Open the file: " << doc.name << endl;
            } catch (exception) {
                cout << "[Open]: The file is invalid format.";
                return nullptr;
            }
        } else {
            cout << "[Open]: The file is invalid format.";
        }
        fin.close();
    } else {
        cout << "[Open]: Open the file *" << file_name << "* failed. Please make sure the file exist." << endl;
        return nullptr;
    }
    cout << "[Open]: Open the file successfully!" << endl;
    return &doc;
}

void display_cdocment(CDocument * doc) {
    cout << "Start to display a PPT." << endl;
    if (doc == nullptr) {
        cout << "[Display]: Can't display the nullptr. Please open or create a new PPT." << endl;
        return;
    }
    doc->Display();
    return;
}

void pre_print_edit_mode() {
    cout << "[Edit PPT]|--------------------|" << endl;
    cout << "[Edit PPT]| 1 -> New     Page  |" << endl;
    cout << "[Edit PPT]| 2 -> Edit    Page  |" << endl;
    cout << "[Edit PPT]| 3 -> Copy    Page  |" << endl;
    cout << "[Edit PPT]| 4 -> Paste   Page  |" << endl;
    cout << "[Edit PPT]| 5 -> Display Page  |" << endl;
    cout << "[Edit PPT]| ___ -1 to exit ___ |" << endl;
    cout << "[Edit PPT]|--------------------|" << endl << endl;
    return ;
}
// ------------------------------------------------------
void pre_print_type_table() {
    cout << "[Edit][Edit][Create]|--------------------|" << endl;
    cout << "[Edit][Edit][Create]| 1 --> Triangle     |" << endl;
    cout << "[Edit][Edit][Create]| 2 --> Rectangle    |" << endl;
    cout << "[Edit][Edit][Create]| 3 --> Round        |" << endl;
    cout << "[Edit][Edit][Create]| 4 --> Other Graph  |" << endl;
    cout << "[Edit][Edit][Create]|--------------------|" << endl << endl;
    return ;
}

void create_text_box(PPTPage * page) {
    if (page == nullptr) {
        cout << "[Edit][Edit][Create]: The PPT Page creating text box can't be nullptr." << endl;
        return;
    }
    cout << "[Edit][Edit][Create]: Start to create new Text Box." << endl;
    static TextBox text_box;

    int buffer;
    pre_print_type_table();
    cout << "[Edit][Edit][Create]: Please input the Graph Type : ";
    cin >> buffer;
    if (!(buffer <= 4 && buffer >=1)) {
        cout << "[Edit][Edit][Create]: The Graph Type must more than zero and less than five.";
        return;
    }
    text_box.type = buffer;

    cout << "[Edit][Edit][Create]: Please input the Text String: ";
    char str[101];
    cin >> str;
    strcpy(text_box.text_string, str);
    cout << "[Edit][Edit][Create]: Please input the Width      : ";

    cin >> buffer;
    if (buffer <= 0) {
        cout << "[Edit][Edit][Create]: Width must more than zero." << endl;
        return;
    }
    text_box.width = buffer;
    cout << "[Edit][Edit][Create]: Please input the Height     : ";
    cin >> buffer;
    if (buffer <= 0) {
        cout << "[Edit][Edit][Create]: Height must more than zero." << endl;
        return;
    }
    text_box.height = buffer;
    cout << "[Edit][Edit][Create]: Please input the Left       : ";
    cin >> buffer;
    if (buffer < 0) {
        cout << "[Edit][Edit][Create]: Left Position must more than zero." << endl;
        return;
    }
    text_box.left = buffer;
    cout << "[Edit][Edit][Create]: Please input the Top        : ";
    cin >> buffer;
    if (buffer < 0) {
        cout << "[Edit][Edit][Create]: Top Position must more than zero." << endl;
        return;
    }
    text_box.top = buffer;
    cout << "[Edit][Edit][Create]: Please input the Line Width : ";
    cin >> buffer;
    if (buffer <= 0) {
        cout << "[Edit][Edit][Create]: Line Width must more than zero." << endl;
        return;
    }
    text_box.line_width = buffer;
    cout << "[Edit][Edit][Create]: Please input the Line Color : ";
    cin >> buffer;
    if (!((buffer >= 0x000000) && (buffer <= 0xffffff))) {
        cout << "[Edit][Edit][Create]: Line Color must more than zero." << endl;
        return;
    }
    text_box.line_color = buffer;
    cout << "[Edit][Edit][Create]: Please input the Fill Color : ";
    cin >> buffer;
    if (!((buffer >= 0x000000) && (buffer <= 0xffffff))) {
        cout << "[Edit][Edit][Create]: Fill Color must more than zero." << endl;
        return;
    }
    text_box.fill_color = buffer;
    page->AddTextBox(&text_box);

    cout << "[Edit][Edit][Create]: Create Text Box Successfully." << endl;
    return;
}


// ------------------------------------------------------
TextBox * text_box_buffer; // buffer for copy and paste

PPTPage * create_pptpage(CDocument * doc) {
    if (doc == nullptr) {
        cout << "[Edit][Create]The PPT can't be the nullptr." << endl;
        return nullptr;
    }
    cout << "[Edit][Create]Start create new PPT page." << endl;
    doc->AddPage();
    cout << "[Edit][Create]Create PPT page: " << ppt_page_count-1 << " successfully." << endl;
    return doc->Index(ppt_page_count-1);
}

void edit_pptpage(PPTPage * page) {
    if (page == nullptr) {
        cout << "[Edit][Edit]The Page can't be the nullptr." << endl;
        return;
    }
    cout << "[Edit][Edit]Start edit PPT page " << page->GetPageNum() << "." <<endl;

    create_text_box(page);

    cout << "[Edit][Edit]Editing PPT page " << page->GetPageNum() << " over." << endl;
    return;
}

void copy_pptpage(PPTPage * page) {
    if (page == nullptr) {
        cout << "[Edit][Copy]The Page now can't be the nullptr." << endl;
        return;
    }
    cout << "[Edit][Copy]Start copy PPT page now." << endl;
    static PPTPage page_buffer;
    page_buffer = *page;
    ppt_page_buffer = &page_buffer;
    cout << "[Edit][Copy]Copying PPT page is over." << endl;
}

void paste_pptpage(CDocument * doc) {
    if (doc == nullptr) {
        cout << "[Edit][Paste]The PPT can't be nullptr.";
        return;
    }
    if (ppt_page_buffer == nullptr) {
        cout << "[Edit][Paste]Your PASTE buffer is Empty! Please make sure your paste buffer is not NULL!" << endl;
    }
    cout << "[Edit][Paste]Start to paste the PPT page to PPT." << endl;
    doc->Paste(ppt_page_buffer);
    cout << "[Edit][Paste]Pasting page to PPT is over." << endl;
    return;
}

void display_pptpage(PPTPage * page) {
    if (page == nullptr) {
        cout << "[Edit][Display]The Page displaying can't be the nullptr." << endl;
        return;
    }
    cout << "[Edit][Display]Start display PPT page." << endl;
    page->Display();
    cout << "[Edit][Display]Displaying PPT page is over." << endl;
    return;
}

void edit_cdocment(CDocument * doc) {
    cout << "Start to edit a PPT." << endl;
    if (doc == nullptr) {
        cout << "[Edit]: Can't edit the nullptr. Please open or create a new PPT." << endl;
        return;
    }
    PPTPage * page = nullptr;
    bool statu = true;
    int type;
    // the type of edit mode
    pre_print_edit_mode();
    while(statu) {
        cout << "[Edit]: Please input the type of edit mode: ";
        cin >> type;
        switch (type) {
            case -1:
                statu =false;
                break;
            case 1:
                page = create_pptpage(doc);
                break;
            case 2:
                edit_pptpage(page);
                break;
            case 3:
                copy_pptpage(page);
                break;
            case 4:
                paste_pptpage(doc);
                break;
            case 5:
                display_pptpage(page);
                break;
            default:
                cout << "[Edit]Please input the type from 1 to 5. Or -1 to exit." << endl;
        }
    }
    return;
}

void pre_print_mode() {
    cout << "|--------------------|" << endl;
    cout << "| 1 -> New     PPT   |" << endl;
    cout << "| 2 -> Save    PPT   |" << endl;
    cout << "| 3 -> Open    PPT   |" << endl;
    cout << "| 4 -> Display PPT   |" << endl;
    cout << "| 5 -> Edit    PPT   |" << endl;
    cout << "| ___ -1 to exit ___ |" << endl;
    cout << "|--------------------|" << endl << endl;
    return ;
}


int main() {
    CDocument * doc = nullptr;
    pre_print_mode();
    char file_name[100];
    int type;
    bool statu = true;
    while (statu) {
        cout << "Now input the type(-1, 1~5): ";
        cin >> type;
        switch (type) {
            case -1:
                statu = false;
                break;
            case 1:
                doc = create_cdocment();
                break;
            case 2:
                save_cdocment(doc);
                break;
            case 3: {
                CDocument * new_doc = open_cdocment();
                if (new_doc != nullptr) {
                    doc = new_doc;
                }
                break;
            }
            case 4:
                display_cdocment(doc);
                break;
            case 5:
                edit_cdocment(doc);
                break;
            default:
                cout << "Please input the type from 1 to 5. Or -1 to exit." << endl;
        }
    }
    cout << "<******Exit Now******>" << endl;
    return 0;
}