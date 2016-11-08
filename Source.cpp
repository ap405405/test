#include <iostream>
#include <vector>
// linear regression < deep learning < machine learning
class LinearHypothesis
{
public:
	// linear hypothesis : y = a * x + b
	float a_ = 0.0f;
	float b_ = 0.0f;
	float c_ = 0.0f;
	float getY(const float& x_input)
	{
		return a_ * x_input*x_input + b_*x_input+c_; // returns y = a*x+b
	}
};


int main()
{
	std::vector<float> study_time_data;
	std::vector<float> score_data;

	const int num_data = 30;
	for (float i = 0.0; i < num_data; i++)
		study_time_data.push_back(i);

	for (float i = 0.0; i < num_data; i++)
		score_data.push_back(3.0*study_time_data[i] + 1 + rand() / RAND_MAX);

	/*const float study_time_data[num_data] = { 0, 1, 2,0,1,2,0, 1, 2,0,1,2,0, 1, 2,0,1,2,0, 1, 2,0,1,2,0, 1, 2,0,1,2};
	const float score_data[num_data] = { 0, 2, 4,0, 2, 4,0, 2, 4,0, 2, 4,0, 2, 4,0, 2, 4,0, 2, 4,0, 2, 4,0, 2, 4 ,0, 2, 4 };*/
	/*const int num_data = 10;
	const int num_n = 0;
	float study_time_data[num_data] = {};
	float score_data[num_data] = {};
	for (int i = 0; i < num_data; i++)
	{
	study_time_data[i] = i;
	}
	for (int i = 0; i < num_data; i++)
	{
	score_data[i] = 3.0*study_time_data[i] + 1 + rand() / RAND_MAX;
	}*/
	LinearHypothesis lh;

	for (int tr = 0; tr < 20000; tr++)
		for (int i = 0; i < num_data; i++)
		{
			// let's train our linear hypothesis to answer correctly!
			const float x_input = study_time_data[i];
			const float y_output = lh.getY(x_input);
			const float y_target = score_data[i];
			const float error = y_output - y_target;
			// we can consider that our LH is trained well when error is 0 or small enough
			// we define squared error
			const float sqr_error = 0.5 * error * error; // always zero or positive

														 // we want to find good combination of a and b which minimizes sqr_error

														 // sqr_error = 0.5 * (a * x + b - y_target)^2
														 // d sqr_error / da = 2*0.5*(a * x + b - y_target) * x; 
														 // d sqr_error / db = 2*0.5*(a * x + b - y_target) * 1;

			const float dse_over_da = error * x_input*x_input;
			const float dse_over_db = error*x_input;

			// need to find good a and b
			// we can update a and b to decrease squared error
			// this is the gradient descent method
			// learning rate
			const float lr = 0.000001; // small number
			lh.a_ -= dse_over_da * lr;
			lh.b_ -= dse_over_db * lr;

			std::cout << "x_input=" << x_input << " y_target=" << y_target
				<< " y_output=" << y_output << " sqr_error = " << sqr_error << std::endl;
		}

	// trained hypothesis
	std::cout << "From trained hypothesis " << "a_= "<<lh.a_<<"b_= "<<lh.b_<<"c_= "<<lh.c_<<"3.5= "<< lh.getY(3.5)<< std::endl;

	return 0;
}