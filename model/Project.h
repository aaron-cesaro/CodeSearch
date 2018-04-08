#ifndef CODESEARCH_PROJECT_H
#define CODESEARCH_PROJECT_H

#include <string>

enum codeLanguage {C, Python, Java, Scala, Go};

class Project {

private:
    std::string name;
    std::string author;
    std::string language;
    std::string projectType;
    std::string license;

public:
    //constructor
    Project(std::string, std::string, std::string, std::string, std::string);

    //get methods
    std::string getName() const;
    std::string getAuthor() const;
    std::string getLanguage() const;
    std::string getProjectType() const;
    std::string getLicense() const;

    //insert/change methods
    void setName(std::string);
    void setAuthor(std::string);
    void setLanguage(std::string);
    void setProjectType(std::string);
    void setLicense(std::string);

};


#endif //CODESEARCH_PROJECT_H
