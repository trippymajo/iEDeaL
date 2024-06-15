#ifndef EDLFILE_H
#define EDLFILE_H

class EdlFile : public QTextStream
{
  // Constructor & Destructor
public:
  EdlFile(FILE* fileHandle);
  ~EdlFile();


};

#endif //EDLFILE_H
