#pragma once

#include <vector>
#include <string>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

enum class PluginType {
  solver = 1,
  dumper,
};

enum class ViewpointType {
  Unknown = 0,
  Voltage,
  Current,
};

struct Viewpoint {
  std::string   name;
  ViewpointType type;
  double       *valuePtr;
};

class Dumper {
protected:
  std::string             fileName;
  FILE                   *p_file;
  std::vector<Viewpoint>  viewpoints;
public:
  Dumper();
public:
  void AddViewpoint(std::string &_name, ViewpointType _vpt, double *_val);
public:
  virtual void BeginDump(std::string &_fileName) = 0;
  virtual void WriteHeader() = 0;
  virtual void WriteValuesAtTime(double _t) = 0;
  virtual void EndDump() = 0;
};


class Dumper_My : public Dumper {
public:
  void BeginDump(std::string &_fileName);
  void WriteHeader();
  void WriteValuesAtTime(double _t);
  void EndDump();
};

__declspec(dllexport) PluginType GetType();
__declspec(dllexport) void GetStringID(std::string &_id);
__declspec(dllexport) Dumper *GetDumper();
__declspec(dllexport) void FreeDumper(Dumper *_p_solver);
