#ifndef PID_H
#define PID_H

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  
  /**
  * Twiddle.
  */
  bool Twiddle();
  
  /**
   * Set private variable: max_steps
   * @param steps
   */
  void Settwiddle_steps(int e_steps, int s_steps);
  
 private:
  /**
   * PID Errors
   */
  double p_err;
  double i_err;
  double d_err;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;
  
  int iter;
  int settle_steps;
  int eval_steps;
  double tolerance;
  double total_err;
  double best_err;

  double Dpp;
  double Dpi;
  double Dpd;

  bool increasing = true;
  int twiddle_index;
};

#endif  // PID_H