#include "HTMLNode.hpp"

pair<string, string> TagNode::getAttribute(int index)
{
    return this->attributes[index];
}

int TagNode::getNumberOfAttributes()
{
    return this->attributes.size();
}

int TagNode::getNumberOfChildrenNodes()
{
    return this->childrenNodes.size();
}

HTMLNode *TagNode::getChildrenNode(int index)
{
    return this->childrenNodes[index];
}

void TagNode::addAttribute(string attributeName, string attributeValue)
{
    this->attributes.push_back(make_pair(attributeName, attributeValue));
}

void TagNode::addChild(HTMLNode *child)
{
    this->childrenNodes.push_back(child);
}

string TagNode::getTagName()
{
    return this->tagName;
}

void TagNode::setTagName(string t)
{
    this->tagName = t;
}

TagNode::TagNode(string tagName)
{
    this->tagName = tagName;
    this->isTextNode = false;
}


std::string TextNode::getContent()
{
    return this->content;
}


TextNode::TextNode(string content)
{
    this->content = content;
    this->isTextNode = true;
}


std::ostream& operator<<(std::ostream& os, TextNode& textNode)
{
    os << "Text node: " << textNode.getContent() << '\n';
    return os;
}

std::ostream& operator<<(std::ostream& os, TagNode& tagNode)
{
    os << "Tag node: " << tagNode.getTagName() << " attributes: ";
    for(int i = 0; i < tagNode.getNumberOfAttributes(); ++i)
    {
        os << tagNode.getAttribute(i).first << " " << tagNode.getAttribute(i).second << " ";
    }

    os << "number of children: " << tagNode.getNumberOfChildrenNodes() << '\n';
    return os;
}