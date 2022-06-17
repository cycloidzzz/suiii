#include <glog/logging.h>

#include <iostream>

#include "lp_lib.h"

int main() {
  DLOG(INFO) << "Hello World!" << std::endl;

  lprec *lp;
  lp = make_lp(0, 2);

  int *lp_column = new int[2]();
  REAL *lp_row = new REAL[2]();

  // open row mode
  set_add_rowmode(lp, 1);

  // add constraint: x1 + 2x2 <= 40
  lp_column[0] = 1;
  lp_row[0] = 1;

  lp_column[1] = 2;
  lp_row[1] = 2;

  add_constraintex(lp, 2, lp_row, lp_column, LE, 40);

  // add constraint: 4x1 + 3x2 <= 120
  lp_column[0] = 1;
  lp_row[0] = 4;

  lp_column[1] = 2;
  lp_row[1] = 3;

  add_constraintex(lp, 2, lp_row, lp_column, LE, 120);

  // add constraint: x1 >= 0
  lp_column[0] = 1;
  lp_row[0] = 1;
  add_constraintex(lp, 1, lp_row, lp_column, GE, 0);

  // add constraint: x2 >= 0
  lp_column[0] = 2;
  lp_row[0] = 1;
  add_constraintex(lp, 1, lp_row, lp_column, GE, 0);

  // close row mode
  set_add_rowmode(lp, 0);

  // add maximum objective: 40x1 + 50x2
  lp_column[0] = 1;
  lp_row[0] = 40;

  lp_column[1] = 2;
  lp_row[1] = 50;
  set_obj_fnex(lp, 2, lp_row, lp_column);

  // set maximum mode
  set_maxim(lp);

  write_LP(lp, stdout);
  // set_verbose(lp, IMPORTANT);

  int ret = solve(lp);

  if (!ret) {
    get_variables(lp, lp_row);

    for (int i = 0; i < 2; i++) {
      DLOG(INFO) << "result of x[" << i << "] = " << lp_row[i] << std::endl;
    }

  } else {
    DLOG(ERROR) << "Could not solve lp" << std::endl;
  }

  delete[] lp_column;
  delete[] lp_row;

  delete_lp(lp);

  return 0;
}