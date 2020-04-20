#include "PID.h"
#include <iostream>
#include <math.h>
using namespace std;
/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  
  p_err = 0;
  i_err = 0;
  d_err = 0;

  iter = 0;
  settle_steps = 100;
  eval_steps = 500;
  tolerance = 0.2;
  total_err = 0;
  best_err = 1000;

  Dpp = Kp*0.1;
  Dpi = Ki*0.1;
  Dpd = Kd*0.1;

  increasing = true;
  twiddle_index = 2;
}

void PID::Settwiddle_steps(int e_step, int s_step){
  eval_steps = e_step;
  settle_steps = s_step;
}
void PID::UpdateError(double cte) {
  /**
   * Update PID errors based on cte.
   */
  d_err = cte-p_err;
  p_err = cte;
  i_err += cte;
  iter += 1;

  // cout << "iter:" << iter << " CTE: " << cte << endl;          
}

double PID::TotalError() {
  /**
   * Calculate and return the total error
   */
  double output = -Kp * p_err- Kd * d_err - Ki * i_err;
  //  std::cout << "P:" << Kp << ", I:" << Ki << ", D:" << Kd << ", value:" << output << std::endl;
  return output;
}

bool PID::Twiddle() {
  bool to_reset = false;
  if (iter % (settle_steps + eval_steps) > settle_steps) {
    total_err += pow(p_err,2);
  }
  
  // Twiddle evaluation
  if((iter % (settle_steps + eval_steps) == 0 )){
    cout << "############################## TWIDDLING ##############################" << endl;
    double err = total_err/eval_steps;
    
    cout << "best_err = " << best_err << endl;
    cout << "err = " << err << endl;
    cout << "Dpp = " << Dpp << ", Dpi = " << Dpi << ", Dpd = " << Dpd << endl;
    cout << "P:" << Kp << ", I:" << Ki << ", D:" << Kd << endl;

    if (err < best_err) {
      cout << "---Improved---Twiddle index" << twiddle_index << endl;
      switch (twiddle_index % 3) {
        case 0:
          Dpp *= 1.1;
          if(Ki != 0.0){
            Ki += Dpi;
          }
          else{
            twiddle_index++;
            Kd += Dpd;
          }
          break;
        case 1:
          Dpi *= 1.1;
          Kd += Dpd;
          break;
        case 2:
          Dpd *= 1.1;
          Kp += Dpp;
          break;
      }
      best_err = err;
      increasing = true;
      cout << "Dpp = " << Dpp << ", Dpi = " << Dpi << ", Dpd = " << Dpd << endl;
      cout << "P:" << Kp << ", I:" << Ki << ", D:" << Kd << endl;
   } else {
      cout << "***Not improved***Twiddle Index***" << twiddle_index << endl;
      switch (twiddle_index % 3) {
        case 0: 
          Kp -= 2*Dpp;
          Dpp *= 0.9;
          if(Ki != 0.0){
            Ki += Dpi;
          }
          else{
            twiddle_index++;
            Kd += Dpd;
          }
          break;
        case 1: 
          Ki -= 2*Dpi;
          Dpi *= 0.9;
          Kd += Dpd;
          break;
        case 2: 
          Kd -= 2*Dpd;
          Dpd *= 0.9;
          Kp += Dpp;
          break;
      }
      cout << "Dpp = " << Dpp << ", Dpi = " << Dpi << ", Dpd = " << Dpd << endl;
      cout << "P:" << Kp << ", I:" << Ki << ", D:" << Kd << endl;

    } 
    twiddle_index++;
  }
  return to_reset;
}
