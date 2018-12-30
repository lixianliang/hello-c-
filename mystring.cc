#include <string.h>

#include <iostream>

class MyString {
public:
    MyString(const char* str = nullptr) {
        if (str == nullptr) {
            data_ = new char[1];
            *data_ = '\0';
            length_ = 0;
        } else {
            int len = strlen(str) + 1;
            length_ = len;
            data_ = new char[len];
            strcpy(data_, str); // strcpy include \0
        }
    }

    MyString(const MyString& str) {
        if (&str != this) {
            int len = strlen(str.data_) + 1;
            delete[] data_;
            length_ = len;
            data_ = new char[len];
            strcpy(data_, str.data_);
        }
    }

    MyString& operator=(const MyString& str) {
        if (&str != this) {
            int len = strlen(str.data_) + 1;
            delete[] data_;
            length_ = len;
            data_ = new char[len];
            strcpy(data_, str.data_);
        }
        return *this;

        /*if(&str!=this)
        {
            MyString strTemp(str);

            char * temp = strTemp.m_data;
            strTemp.m_data = m_data;
            m_data = temp;
        }
        return *this;*/
        // 可避免异常问题，delete后new失败了
    }

    MyString operator+(const MyString& str) const {
        // 返回一个新的字符串
        MyString new_str;
        new_str.length_ = length_ + str.length_;
        new_str.data_ = new char[new_str.length_ + 1];
        strcpy(new_str.data_, data_);
        strcat(new_str.data_, str.data_);
        return new_str;
    }


    MyString& operator+=(const MyString& str) {
        length_ += str.length_;
        char* new_data = new char[length_ + 1];
        strcpy(new_data, data_);
        strcat(new_data, str.data_);    // append
        delete[] data_;
        data_ = new_data;
        return *this;
    }

    bool operator==(const MyString& str) const {
        if (length_ != str.length_) {
            return false;
        }
        return strcmp(data_, str.data_) ? false: true;
    }

    char& operator[](int n) const{
        if (n >= length_) {
            return data_[length_-1]; // 错误处理
        } else {
            return data_[n];
        }
    }

    virtual ~MyString() {
        if (data_ != nullptr) {
            length_ = 0;
            delete[] data_;
            data_ = nullptr;
        }
    }

    const char* data() const {
        return data_;
    }

private:
    char* data_;
    int length_;
};

int main(int argc, char *argv[]) {
    char a[] = "Hello", b[] = "World";
    MyString s1(a), s2(b);
    std::cout << s1.data() << std::endl;
    std::cout << s2.data() << std::endl;
    s1 += s2;
    std::cout << s1.data() << std::endl;
    return 0;
}
