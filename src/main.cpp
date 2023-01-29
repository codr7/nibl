#include <functional>
#include <iostream>

#include "nibl/vm.hpp"
#include "nibl/repl.hpp"

using namespace std;

using Args = deque<string>;

static nibl::E load_args(nibl::VM &vm, Args &args) {
  for (const string &arg: args) {
    nibl::Pos pos(arg, 1, 1);
    if (auto e = vm.load(arg, pos); e) { return e; }
  }

  return nullopt;
}

static int v_cmd(Args &args) {
  cout << "Nibl v" << nibl::VERSION << endl;
  return 0;
}

static int build_cmd(Args &args) {
  cout << "Not implemented" << endl;
  return 0;
}

static int eval_cmd(Args &args) {
  nibl::Pos pos("init", 1, 1);
  nibl::VM vm(pos);

  if (auto e = vm.root_env.import(vm.abc_lib, {}, pos); e) {
    cout << *e << endl;
    return -1;
  }
  
  if (auto e = load_args(vm, args); e) {
      cout << *e << endl;
      return -1;
  }
  
  return 0;
}

static int help_cmd(Args &args) {
  v_cmd(args);
  
  cout << endl <<
    "Usage: nibl [command] [file1.nl] [file2.nl]" << endl << endl <<
    "Commands:" << endl <<
    "build\tBuild executable" << endl <<
    "eval\tEvaluate and exit" << endl << 
    "repl\tStart repl" << endl <<
    "v\tPrint version and exit" << endl;
  
  return 0;
}

static int repl_cmd(Args &args) {
  v_cmd(args);
  cout << endl;
  
  nibl::Pos pos("init", 1, 1);
  nibl::VM vm(pos);

  if (auto e = vm.root_env.import(vm.abc_lib, {}, pos); e) {
    cout << *e << endl;
    return -1;
  }

  if (auto e = load_args(vm, args); e) {
      cout << *e << endl;
      return -1;
  }

  nibl::repl(vm);
  return 0;
}

using Cmd = function<int (Args &args)>;

int main(int argc, char *argv[]) {
  static const map<string, Cmd> cmds = {
    {"build", build_cmd}, {"eval", eval_cmd}, {"help", help_cmd}, {"repl", repl_cmd}, {"v", v_cmd}
  };
  
  optional<Cmd> cmd;
  int i = 1;
  
  if (argc > 1) {
    auto found = cmds.find(argv[1]);
    if (found != cmds.end()) {
      cmd = found->second;
      i++;
    }
  }

  if (!cmd) { cmd = (argc == 1) ? repl_cmd : eval_cmd; }

  Args args;
  for (; i < argc; i++) { args.push_back(argv[i]); }
  return (*cmd)(args);
}
