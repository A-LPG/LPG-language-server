/*
 *  optionParser.cpp
 *  lpg
 *
 *  Created by Robert M. Fuhrer on 3/21/11.
 *  Copyright 2011 IBM.
 */

#include "JikesPGOptions.h"


OptionParser::OptionParser(const std::list<OptionDescriptor*> opts)
{
    allOptions = opts;
}

bool
OptionParser::IsDelimiter(char c)
{
    return (c == NULL_CHAR || c == ',' || Code::IsSpace(c));
}

OptionDescriptor *
OptionParser::findOption(const char *&start, bool& noFlag)
{
    for (std::list<OptionDescriptor*>::iterator iter=allOptions.begin(); iter != allOptions.end(); iter++) {
        OptionDescriptor *od = *iter;
        const char *p = start;
        const char *word1 = od->getWord1();
        const char *word2 = od->getWord2();

        if ((*p == 'n' || *p == 'N') && (*(p+1) == 'o' || *(p+1) == 'O')) {
            p += 2;
            noFlag = true;
        } else {
            noFlag = false;
        }

        if(!od->isWordIgnoreCase())
        {
            if ((p[0] == *word1 || p[0] == ToUpper(*word1)) &&
                (word2 != NULL && (p[1] == *word2 || p[1] == ToUpper(*word2)) &&
                    (p[2] == '=' || IsDelimiter(p[2])) ||
                    word2 == NULL && (p[2] == '=' || IsDelimiter(p[2])))) {
                start += 2;
                return od;
            }
        }
        else
        {
            if ((  p[0] == *word1 || ToUpper(p[0]) == ToUpper(*word1)) &&
                (word2 != NULL && (p[1] == *word2 || ToUpper(p[1]) == ToUpper(*word2)) &&
                    (p[2] == '=' || IsDelimiter(p[2])) ||
                    word2 == NULL && (p[2] == '=' || IsDelimiter(p[2])))) {
                start += 2;
                return od;
            }
        }
        
        int length1 = strlen(word1);
        int length = length1 + strlen(word2) + 1; // +1 for separator
        char *name = new char[length + 1];
        
        strcpy(name, word1);
        strcat(name, word2);
        int i = strxsub(p, name) - 1;
        
        strcpy(name, word1);
        strcat(name, "_");
        strcat(name, word2);
        
        i = Max(i, strxsub(p, name) - 1);
        
        name[length1] = '-';
        
        i = Max(i, strxsub(p, name) - 1);
        
        delete [] name;
        
        if (p[i+1] == '=' || IsDelimiter(p[i+1])) {
            start += i + 1;
            if (noFlag) {
                start += 2;
            }
            return od;
        }
    }
    return NULL;
}

std::string *
OptionParser::getOptionValue(const char *&p)
{
    if (p != NULL && *p == '=') {
        int plen = strlen(p+1);
        const char *delim;
        
        if (p[1] == '(') {
            // A parenthesized string list
            delim = strchr(p, ')');
            delim = strchr(delim, ',');
        } else {
            delim = strchr(p, ',');
        }
        
        int len = (delim != NULL) ? delim - p - 1 : plen;
        std::string *result = new std::string(p+1, len);
        
        p += result->length() + 1;
        return result;
    }
    return NULL;
}

std::unique_ptr<OptionValue> OptionParser::parse(const char *&start)
{
    return  parse(start, {});
}

std::unique_ptr<OptionValue> OptionParser::parse(const char*& start, const std::set<OptionDescriptor*>& exclude)
{
    bool noFlag;
    OptionDescriptor* od = findOption(start, noFlag);

    if (od != NULL) {
        if (exclude.find(od) != exclude.end()) return  nullptr;
        // This option is a match
        std::string* optValueStr = getOptionValue(start);
        OptionValue* optValue = od->createValue(noFlag);
    	
        if (!optValue)return nullptr;
    	
        optValue->parseValue(optValueStr);
        //        // HACK Handle the "no" prefix on boolean options
        if (od->getType() == BOOLEAN_TYPE && !noFlag) {
            BooleanOptionValue* bv = static_cast<BooleanOptionValue*> (optValue);
            bv->setValue(!bv->getValue());
        }
        return std::unique_ptr<OptionValue>(optValue);
    }
    return nullptr;
}
