#include <iostream>
#include <vector>

class LinearHypothesis
{
public:
	
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

	const int num_data = 20;
	for (float i = 0.0; i < num_data; i++)
		study_time_data.push_back(i);

	for (float i = 0.0; i < num_data; i++)
		score_data.push_back(3.0*study_time_data[i] + 1 + rand() / RAND_MAX);

	
	LinearHypothesis lh;

	for (int tr = 0; tr < 10000; tr++)
		for (int i = 0; i < num_data; i++)
		{
			
			const float x_input = study_time_data[i];
			const float y_output = lh.getY(x_input);
			const float y_target = score_data[i];
			const float error = y_output - y_target;
			
			const float sqr_error = 0.5 * error * error; 

			const float dse_over_da = error * x_input*x_input;
			const float dse_over_db = error*x_input;

			const float lr = 0.000001;
			lh.a_ -= dse_over_da * lr;
			lh.b_ -= dse_over_db * lr;

			std::cout << "x_input=" << x_input << " y_target=" << y_target
				<< " y_output=" << y_output << " sqr_error = " << sqr_error << std::endl;
		}

	std::cout << "From trained hypothesis " << "a_= "<<lh.a_<<"b_= "<<lh.b_<<"c_= "<<lh.c_<< std::endl;

	return 0;
}
