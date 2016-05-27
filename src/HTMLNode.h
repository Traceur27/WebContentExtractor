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
};


class TagNode : HTMLNode
{
private:
    string tagName;
    vector<pair<string, string>> attributes;
    vector<HTMLNode *> childrenNodes;

public:
    HTMLNode* getParent();
    pair<string, string> getAttribute(int index);
    void addAttribute(string attributeName, string attributeValue);
    void addChild(HTMLNode * child);
    HTMLNode * getChildrenNode(int index);
    int getNumberOfAttributes();
    int getNumberOfChildrenNodes();
    string getTagName();
    void setTagName(string t);

};

class TextNode : HTMLNode
{
private:
    string content;

public:
    HTMLNode* getParent();
    void setParent(HTMLNode* p);
    string getContent();
};


std::ostream& operator<<(std::ostream& os, TextNode& textNode);
std::ostream& operator<<(std::ostream& os, TagNode& tagNode);

#endif //WEB_CONTENT_EXTRACTOR_HTMLNODE_H
