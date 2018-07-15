//
// Created by Yaser Alkayale on 2018-07-15.
//

#ifndef BIGINT2_BIGINTEXCEPTIONS_H
#define BIGINT2_BIGINTEXCEPTIONS_H
#include<exception>
#include<string>
namespace bigint{
class Exception : std::exception{

public:
  //Constants
  enum ErrorTypes{
    USER_ERROR,
    INTERNAL_ERROR
  };

  Exception(const ErrorTypes errorType, const int& lineNumber, const char* fileName, const char* message):msg_(std::string(message)),lineNumber_(lineNumber),fileName_(fileName){};
  //coloring reference
  //https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
  std::string what(){
    return "\033[1;31mERROR: "+msg_+std::string("\n\tFile: ")+fileName_+std::string("\n\tLine: ")+std::to_string(lineNumber_)+std::string("\033[0m");
  }
private:
  const int lineNumber_;
  std::string fileName_;
  std::string msg_;

};
}


#endif //BIGINT2_BIGINTEXCEPTIONS_H
