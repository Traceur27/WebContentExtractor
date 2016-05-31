#ifndef WEB_CONTENT_EXTRACTOR_HTMLNODE_H
#define WEB_CONTENT_EXTRACTOR_HTMLNODE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class HTMLNode
{
protected:
    HTMLNode * parent;
    bool isTextNode;

public:
    bool checkIfIsTextNode() {return isTextNode;}
    void setParent(HTMLNode * p) {this->parent = p;}
    HTMLNode* getParent() {return this->parent;}
};


class TagNode : public HTMLNode
{
private:
    string tagName;
    vector<pair<string, string> > attributes;
    vector<HTMLNode *> childrenNodes;

public:
    TagNode(string tagName);
    pair<string, string> getAttribute(int index);
    void addAttribute(string attributeName, string attributeValue);
    void addChild(HTMLNode * child);
    HTMLNode * getChildrenNode(int index);
    int getNumberOfAttributes();
    int getNumberOfChildrenNodes();
    string getTagName();
    void setTagName(string t);

};

class TextNode : public HTMLNode
{
private:
    string content;

public:
    TextNode(string content);
    string getContent();
};


std::ostream& operator<<(std::ostream& os, TextNode& textNode);
std::ostream& operator<<(std::ostream& os, TagNode& tagNode);

#endif //WEB_CONTENT_EXTRACTOR_HTMLNODE_H
