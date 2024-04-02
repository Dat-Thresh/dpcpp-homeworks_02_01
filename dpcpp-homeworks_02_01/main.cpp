#include <iostream>
#include <string>
#include <utility>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

//параграф
class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {};
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};
//реверс 
class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {};
    void render(const std::string& data) const override {
        auto buf = data;
        std::reverse(buf.begin(), buf.end());
        text_->render(buf);
    }
};

//создание ссылки
class Link : public DecoratedText {
public:
    explicit Link(Text* text) :DecoratedText(text) {}
    void render(const std::string& data) = delete;
    void render(const std::string& link, const std::string& data) const{
        std::cout << "<a href=" + link + ">";
        text_->render(data);
        std::cout << "</a>";
    }
};
int main() {
    auto text_block = new Link(new Reversed (new Paragraph(new DecoratedText(new Text()))));
    text_block->render("netology.ru", "Hello_world");
   // text_block->render("Hello_world!");




    return 0;
}
