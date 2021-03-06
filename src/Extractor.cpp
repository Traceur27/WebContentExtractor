#include "Extractor.hpp"

Extractor::Extractor(string configFileName, string sourceFileName)
{
    this->configuration.setFileName(configFileName);
    this->configuration.init();
    this->source.setFileName(sourceFileName);
    this->source.init();
}


void Extractor::startExtracting()
{
    this->configuration.parse();
    this->source.parse();
    // this->configuration.listNodes(this->configuration.getRoot());
    //cout << "\n\n";
    //this->source.listNodes(this->source.getRoot());
    // cout << "\n\n";
    extract(this->configuration.getRoot(), this->source.getRoot(), false);
}



void Extractor::extract(HTMLNode *config, HTMLNode *source, bool f)
{
    if(config != nullptr)
    {
        if(config->checkIfIsTextNode())
        {
            TagNode * parent;
            if(!f)
                parent = (TagNode *)source->getParent();
            else
                parent = (TagNode*)source;

            TextNode * tNode = (TextNode *)config;
            string attributeName = tNode->getContent();
            for(int i = 0; i < parent->getNumberOfAttributes(); ++i)
            {
                if(parent->getAttribute(i).first == attributeName)
                {
                    cout << parent->getAttribute(i).second << endl;
                    break;
                }
            }
            return;
        }
        else
        {
            TagNode *configNode = (TagNode *)config;
            TagNode *sourceNode = (TagNode *)source;

            if(configNode->getNumberOfChildrenNodes() == 0)
            {
                //Przejdź przez wszystkie węzły dzieci source szukając textowego
                for(int i = 0; i < sourceNode->getNumberOfChildrenNodes(); ++i)
                {
                    if(sourceNode->getChildrenNode(i)->checkIfIsTextNode())
                    {
                        TextNode * tNode = (TextNode *)sourceNode->getChildrenNode(i);
                        cout << tNode->getContent() << endl;
                        return;
                    }
                }
            }

            for(int i = 0; i < configNode->getNumberOfChildrenNodes(); ++i)
            {
                HTMLNode * nextConfigNode = configNode->getChildrenNode(i);
                HTMLNode * nextSourceNode = nullptr;

                for (int i = 0; i < sourceNode->getNumberOfChildrenNodes(); ++i)
                {
                    if(compareNodes(nextConfigNode, sourceNode->getChildrenNode(i)))
                    {
                        nextSourceNode = sourceNode->getChildrenNode(i);
                        break;
                    }
                }
                if(nextSourceNode == nullptr)
                {
                    nextSourceNode = sourceNode;
                    extract(nextConfigNode, nextSourceNode, true);
                }
                else
                    extract(nextConfigNode, nextSourceNode, false);
            }
        }
    }
}


bool Extractor::compareNodes(HTMLNode *first, HTMLNode *second)
{
    if(first->checkIfIsTextNode() && second->checkIfIsTextNode())
    {
        return true;
    }
    else if(!first->checkIfIsTextNode() && !second->checkIfIsTextNode())
    {
        TagNode * t1 = (TagNode *)first;
        TagNode * t2 = (TagNode *)second;

        if(compareTagNodes(t1, t2))
            return true;
        return false;
    }
    else
        return false;
}

bool Extractor::compareTagNodes(TagNode *t1, TagNode *t2)
{
    if(t1->getTagName() == t2->getTagName() && t1->getNumberOfAttributes() == t2->getNumberOfAttributes())
    {
        for(int i = 0; i < t1->getNumberOfAttributes(); ++i)
        {
            if(t1->getAttribute(i) != t2->getAttribute(i))
                return false;
        }
        return true;
    }
    else
        return false;
}