/*
https://www.hackerrank.com/challenges/attribute-parser/

This challenge works with a custom-designed markup language HRML.
In HRML, each element consists of a starting and ending tag, and there are attributes associated with each tag.
Only starting tags can have attributes. We can call an attribute by referencing the tag, followed by a tilde, '~' and the name of the attribute.
The tags may also be nested.

The opening tags follow the format:
<tag-name attribute1-name = "value1" attribute2-name = "value2" ...>

The closing tags follow the format:
</tag-name>

The attributes are referenced as:
tag1~value
tag1.tag2~name
Given the source code in HRML format consisting of  lines, answer  queries. For each query, print the value of the attribute specified. Print "Not Found!" if the attribute does not exist.

Example
HRML listing
<tag1 value = "value">
<tag2 name = "name">
<tag3 another="another" final="final">
</tag3>
</tag2>
</tag1>

Queries
tag1~value
tag1.tag2.tag3~name
tag1.tag2~value
Here, tag2 is nested within tag1, so attributes of tag2 are accessed as tag1.tag2~<attribute>. Results of the queries are:

Query                 Value
tag1~value            "value"
tag1.tag2.tag3~name   "Not Found!"
tag1.tag2.tag3~final  "final"

<a value = "GoodVal">
    <b value = "BadVal" size = "10">
    </b>
    <c height = "auto">
        <d size = "3">
            <e strength = "2">
            </e>
        </d>
    </c>
</a>
*/

#include <bits/stdc++.h>
#include <sstream>

bool isOpenningTag(const std::string &tag)
{
    return (tag[0] == '<' && tag[1] != '/');
}

bool isClosingTag(const std::string &tag)
{
    return (tag[0] == '<' && tag[1] == '/');
}

class Tag
{
private:
    std::string name;
    std::unordered_map<std::string, std::string> attributes;
    std::unordered_map<std::string, Tag *> children;

public:
    Tag(const std::string &name) : name(name) {}

    std::string getName() const
    {
        return this->name;
    }

    void addAttribute(const std::string &attr, const std::string &value)
    {
        attributes[attr] = value;
    }

    std::string getAttribute(const std::string &attr) const
    {
        auto it = this->attributes.find(attr);
        if (it != this->attributes.end())
        {
            return it->second;
        }
        else
        {
            return "Not Found!";
        }
    }

    void setChild(const std::string &name, Tag *child)
    {
        if (child == nullptr)
            return;

        this->children[name] = child;
    }

    Tag *getChild(const std::string &name) const
    {
        auto it = this->children.find(name);
        if (it != this->children.end())
        {
            return it->second;
        }
        else
        {
            return nullptr;
        }
    }

    std::unordered_map<std::string, Tag *> getChildren() const
    {
        return this->children;
    }

    friend std::ostream &operator<<(std::ostream &os, const Tag &tag)
    {
        static int indentLevel = 0;
        std::string indent(indentLevel * 4, ' ');

        os << indent << "<" << tag.name;
        for (const auto &attr : tag.attributes)
        {
            os << " " << attr.first << "=\"" << attr.second << "\"";
        }
        os << ">" << std::endl;

        indentLevel++;
        for (const auto &child : tag.children)
        {
            os << *(child.second);
        }
        indentLevel--;

        os << indent << "</" << tag.name << ">" << std::endl;

        return os;
    }
};

class TagTree
{
private:
    Tag *rootTag = nullptr;
    std::unordered_map<std::string, Tag *> tagMap;
    std::stack<Tag *> tagStack;
    std::stack<Tag *> completedTagStack;

public:
    TagTree() {};

    void buildTree(std::vector<std::string> lines)
    {
        for (std::string line : lines)
        {
            if (isOpenningTag(line))
            {
                std::stringstream ss(line);

                std::string tagName;
                ss >> tagName;

                tagName = tagName.substr(1, std::string::npos);

                Tag *newTag = new Tag(tagName);
                this->tagMap[tagName] = newTag;

                // This tag has attributes
                if (tagName.length() + 1 != line.length())
                {
                    std::string attrStr = line.substr(tagName.length() + 2, line.length() - tagName.length() - 3);

                    ss = std::stringstream(attrStr);
                    std::string attrPair;

                    int cnt = 1;
                    std::string attrName, attrValue;
                    while (ss >> attrPair)
                    {
                        switch (cnt)
                        {
                        case 1:
                            attrName = attrPair;
                            cnt += 1;
                            break;

                        case 2:
                            // This is the '=' part
                            cnt += 1;
                            break;

                        case 3:
                            attrValue = attrPair.substr(1, attrPair.length() - 2);
                            cnt += 1;
                            break;
                        }

                        if (cnt > 3)
                        {
                            cnt = 1;
                            newTag->addAttribute(attrName, attrValue);
                        }
                    }
                }

                if (!rootTag)
                {
                    this->rootTag = newTag;
                    this->tagStack.push(rootTag);
                }
                else
                {
                    this->tagStack.push(newTag);
                }
            }
            else if (isClosingTag(line))
            {
                // </tag-name>
                std::string tagName = line.substr(2, line.length() - 3);

                if (tagName == tagStack.top()->getName())
                {
                    Tag *tag = tagStack.top();
                    tagStack.pop();
                    completedTagStack.push(tag);

                    while (!completedTagStack.empty())
                    {
                        Tag *completedTag = completedTagStack.top();
                        this->completedTagStack.pop();

                        // We don't want the root tag to be added as a child of itself
                        if (tagStack.empty())
                        {
                            break;
                        }
                        else
                        {
                            Tag *parentTag = tagStack.top();
                            parentTag->setChild(completedTag->getName(), completedTag);
                        }
                    }
                }
            }
        }
    }

    Tag *getRootTag() const
    {
        return this->rootTag;
    }

    Tag *getTag(const std::string &tagName) const
    {
        auto it = this->tagMap.find(tagName);
        if (it != this->tagMap.end())
        {
            return it->second;
        }
        else
        {
            return nullptr;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const TagTree &tree)
    {
        static int indentLevel = 0;
        std::string indent(indentLevel * 4, ' ');

        os << std::endl;
        if (tree.rootTag)
        {
            os << *(tree.rootTag);
        }
        else
        {
            os << "" << std::endl;
        }

        return os;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::stack<Tag *> tagStack;
    std::stack<Tag *> completedTagStack;
    std::unordered_map<std::string, Tag *> tagMap;

    int N, Q;
    std::cin >> N >> Q;
    std::cin.ignore();

    std::vector<std::string> lines(N);
    // <tag-name attribute1-name = "value1" attribute2-name = "value2" ...>
    for (int i = 1; i <= N; i++)
    {
        std::string line;
        std::getline(std::cin, line);
        lines.push_back(line);
    }

    TagTree tagTree;
    tagTree.buildTree(lines);

    std::cout << tagTree << std::endl;

    for (int i = 1; i <= Q; i++)
    {
        std::string query;
        std::getline(std::cin, query);

        std::stringstream ss(query);

        int separtorIdx = query.find("~");
        std::string tagPath = query.substr(0, separtorIdx);
        std::string attrName = query.substr(separtorIdx + 1, std::string::npos);

        std::string tagName;
        std::vector<std::string> tagNames;
        ss = std::stringstream(tagPath);
        while (getline(ss, tagName, '.'))
        {
            tagNames.push_back(tagName);
        }

        Tag *tag = tagTree.getTag(tagNames[0]);
        Tag *root = tagTree.getRootTag();

        if (tag != root)
        {
            std::cout << "Not Found!" << std::endl;
            continue;
        }
        else
        {
            if (tagNames.size() == 1)
            {
                std::cout << tag->getAttribute(attrName) << std::endl;
            }
            else if (tagNames.size() > 1)
            {
                for (int j = 1; j < tagNames.size(); j++)
                {
                    tag = tag->getChild(tagNames[j]);

                    if (tag == nullptr)
                    {
                        std::cout << "Not Found!" << std::endl;
                        break;
                    }

                    if (j == tagNames.size() - 1)
                    {
                        std::cout << tag->getAttribute(attrName) << std::endl;
                    }
                }
            }
        }
    }

    return 0;
}
