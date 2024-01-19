#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<pthread.h>
#include<iostream>
#include<vector>
#include<string.h>
#include<cmath>
#include <pthread.h>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

vector<vector<vector<double>>> weights=
    { 
         {
             {0.1, -0.2, 0.3, 0.1, -0.2, 0.3, 0.1, -0.2}, 
             {-0.4, 0.5, 0.6, -0.4, 0.5, 0.6, -0.4, 0.5} 
         },
         {
             {-0.2, 0.3, -0.4, 0.5, 0.6, -0.7, 0.8, -0.9},
             {0.1, 0.9, -0.3, 0.2, -0.5, 0.4, 0.6, -0.8},
             {-0.7, 0.5, 0.8, -0.2, -0.3, -0.6, 0.1, 0.4},
             {-0.2, 0.3, -0.4, 0.5, 0.6, -0.7, 0.8, -0.9},
             {0.1, 0.9, -0.3, 0.2, -0.5, 0.4, 0.6, -0.8},
             {-0.7, 0.5, 0.8, -0.2, -0.3, -0.6, 0.1, 0.4},
             {-0.2, 0.3, -0.4, 0.5, 0.6, -0.7, 0.8, -0.9},
             {0.1, 0.9, -0.3, 0.2, -0.5, 0.4, 0.6, -0.8}
         },
         {
             {0.2, -0.3, 0.4, -0.5, -0.6, 0.7, -0.8, 0.9},
             {-0.1, -0.9, 0.3, -0.2, 0.5, -0.4, -0.6, 0.8},
             {0.7, -0.5, -0.8, 0.2, 0.3, 0.6, -0.1, -0.4},
             {0.2, -0.3, 0.4, -0.5, -0.6, 0.7, -0.8, 0.9},
             {-0.1, -0.9, 0.3, -0.2, 0.5, -0.4, -0.6, 0.8},
             {0.7, -0.5, -0.8, 0.2, 0.3, 0.6, -0.1, -0.4},
             {0.2, -0.3, 0.4, -0.5, -0.6, 0.7, -0.8, 0.9},
             {-0.1, -0.9, 0.3, -0.2, 0.5, -0.4, -0.6, 0.8}
         },
         {
             {0.3, -0.4, 0.5, -0.6, -0.7, 0.8, -0.9, 0.1},
             {-0.2, -0.9, 0.4, -0.3, 0.5, -0.6, -0.8, 0.1},
             {0.6, -0.5, -0.7, 0.2, 0.4, 0.8, -0.1, -0.3},
             {0.3, -0.4, 0.5, -0.6, -0.7, 0.8, -0.9, 0.1},
             {-0.2, -0.9, 0.4, -0.3, 0.5, -0.6, -0.8, 0.1},
             {0.6, -0.5, -0.7, 0.2, 0.4, 0.8, -0.1, -0.3},
             {0.3, -0.4, 0.5, -0.6, -0.7, 0.8, -0.9, 0.1},
             {-0.2, -0.9, 0.4, -0.3, 0.5, -0.6, -0.8, 0.1}
         },
         {
             {0.4, -0.5, 0.6, -0.7, -0.8, 0.9, -0.1, 0.2},
             {-0.3, -0.8, 0.5, -0.4, 0.6, -0.7, -0.9, 0.2},
             {0.5, -0.4, -0.6, 0.3, 0.2, 0.8, -0.2, -0.1},
             {0.4, -0.5, 0.6, -0.7, -0.8, 0.9, -0.1, 0.2},
             {-0.3, -0.8, 0.5, -0.4, 0.6, -0.7, -0.9, 0.2},
             {0.5, -0.4, -0.6, 0.3, 0.2, 0.8, -0.2, -0.1},
             {0.4, -0.5, 0.6, -0.7, -0.8, 0.9, -0.1, 0.2},
             {-0.3, -0.8, 0.5, -0.4, 0.6, -0.7, -0.9, 0.2}
         },
         {
             {0.5, -0.6, 0.7, -0.8, -0.9, 0.1, -0.2, 0.3},
             {-0.4, -0.7, 0.6, -0.5, 0.8, -0.6, -0.2, 0.1},
             {0.4, -0.3, -0.5, 0.1, 0.6, 0.7, -0.3, -0.2},
             {0.5, -0.6, 0.7, -0.8, -0.9, 0.1, -0.2, 0.3},
             {-0.4, -0.7, 0.6, -0.5, 0.8, -0.6, -0.2, 0.1},
             {0.4, -0.3, -0.5, 0.1, 0.6, 0.7, -0.3, -0.2},
             {0.5, -0.6, 0.7, -0.8, -0.9, 0.1, -0.2, 0.3},
             {-0.4, -0.7, 0.6, -0.5, 0.8, -0.6, -0.2, 0.1}
         },
         {
             {-0.1},
             {0.2},
             {0.3},
             {0.4},
             {0.5},
             {-0.6},
             {-0.7},
             {0.8}
         }
    };
/*

//-------------------------------------------------------file read-------------------------------------------//
vector<vector<vector<double>>> weights(7, vector < vector < double >>(8, vector<double>(8)));

vector<vector<vector<double>>> read()
{
	ifstream file;
	file.open("data.txt");  // replace with your file path
	string line, str;
	//vector<vector<vector<double>>> weights(7, vector < vector < double >>(8, vector<double>(8)));
	char ch; string tokens[8];
	while (!file.eof())
	{
		getline(file, line);
		if (line == "Input layer weights")
		{
			for (int i = 0; i < 2; i++)
			{
				getline(file, line);
				stringstream ss(line);
				for (int j = 0; j < 8; j++)
				{
					getline(ss, str, ',');
					tokens[j] = str;
				//	cout << tokens[j] << " ";
					weights[0][i][j] = stod(tokens[j]);
				}
			}
		}
		if (line == "Hidden layer 1 weights")
		{
			for (int i = 0; i < 8; i++)
			{
				getline(file, line);
				stringstream ss(line);
				for (int j = 0; j < 8; j++)
				{
					getline(ss, str, ',');
					tokens[j] = str;
					//cout << tokens[j] << " ";
					weights[1][i][j] = stod(tokens[j]);
				}
			}
		}
		if (line == "Hidden layer 2 weights")
		{
			for (int i = 0; i < 8; i++)
			{
				getline(file, line);
				stringstream ss(line);
				for (int j = 0; j < 8; j++)
				{
					getline(ss, str, ',');
					tokens[j] = str;
					//cout << tokens[j] << " ";
					weights[2][i][j] = stod(tokens[j]);
				}
			}
		}
		if (line == "Hidden layer 3 weights")
		{
			for (int i = 0; i < 8; i++)
			{
				getline(file, line);
				stringstream ss(line);
				for (int j = 0; j < 8; j++)
				{
					getline(ss, str, ',');
					tokens[j] = str;
					//cout << tokens[j] << " ";
					weights[3][i][j] = stod(tokens[j]);
				}
			}
		}
		if (line == "Hidden layer 4 weights")
		{
			for (int i = 0; i < 8; i++)
			{
				getline(file, line);
				stringstream ss(line);
				for (int j = 0; j < 8; j++)
				{
					getline(ss, str, ',');
					tokens[j] = str;
					//cout << tokens[j] << " ";
					weights[4][i][j] = stod(tokens[j]);
				}
			}
		}
		if (line == "Hidden layer 5 weights")
		{
			for (int i = 0; i < 8; i++)
			{
				getline(file, line);
				stringstream ss(line);
				for (int j = 0; j < 8; j++)
				{
					getline(ss, str, ',');
					tokens[j] = str;
					//cout << tokens[j] << " ";
					weights[5][i][j] = stod(tokens[j]);
				}
			}
		}
		if (line == "Output layer weights")
		{
			for (int i = 0; i < 8; i++)
			{
				getline(file, line);
				stringstream ss(line);
				getline(ss, str, ',');
				tokens[i] = str;
				//cout << tokens[i] << " ";
				weights[6][i][0] = stod(tokens[i]);
			}
		}
	}
	file.close();
	weights[0].resize(2);
	return weights;
}    */

struct neuron_info{
    vector<double> input_neurons;
    int layer_num;
    int index;
};

pthread_mutex_t m1;
vector<double> output_neurons1;
int count = 0;;

void* cal_neuron(void* arg){
    neuron_info* ni = (neuron_info*) arg;
    pthread_mutex_lock(&m1);
    for(int j=0; j< weights[ni->layer_num].size();j++)
        {   
            output_neurons1[ni->index] += ni->input_neurons[j] * weights[ni->layer_num][j][ni->index]; // h1= input[0]*w1+input[1]*weigth of next input
        }
        //cout << output_neurons1[ni->index];
    count++;
    //cout << ni->index << " " << ni->input_neurons[0];
    pthread_mutex_unlock(&m1);
    delete ni;
    pthread_exit(0);
}

void compute_middle_layers(int layer_num, int read_fd, int write_fd) {
    if(layer_num < 6){
            vector<double> output_neurons(weights[layer_num][0].size());
            vector<double> input_neurons(weights[layer_num][0].size());
            output_neurons1.resize(output_neurons.size());
            // Read input from the previous layer
            read(read_fd, input_neurons.data(), sizeof(double) * input_neurons.size());
            for(int i=0; i< weights[layer_num][0].size();i++)
            {
                neuron_info* ni = new neuron_info();
                ni->input_neurons = input_neurons;
                ni->index = i;
                ni->layer_num = layer_num;

                pthread_t thread;
                pthread_create(&thread, NULL, cal_neuron, ni);
                
            }
            
            while(count <= weights[layer_num][0].size()-1);
           
            output_neurons = output_neurons1;
            cout << "\n_______________neurons of layer "<< layer_num+1 <<"___________________________\n";
            for(int i=0; i< output_neurons.size();i++ )
            {
                cout << output_neurons[i] << " ";
            }
            cout << endl;
            write(write_fd, output_neurons.data(), sizeof(double) * output_neurons.size());
        }

        else{
            vector<double> output_neurons(weights[layer_num][0].size());
            vector<double> input_neurons(weights[layer_num-1][0].size());
            // Read input from the previous layer
            read(read_fd, input_neurons.data(), sizeof(double) * input_neurons.size());
            for(int i=0; i< weights[6].size();i++)
            {
                output_neurons[0] += input_neurons[i] * weights[6][i][0]; 
            }
            cout << "\n_______________output___________________________\n";
            cout << output_neurons[0] << endl;
            write(write_fd, output_neurons.data(), sizeof(double) * output_neurons.size());
        }

    // Write output to the next layer
    
}

vector<double> generate_newoutputs(double input){
    vector<double> outputs;
    outputs.push_back((input*input+input+1)/2);
    outputs.push_back((input*input-input)/2);
    cout << endl <<"Fromula 1: " << outputs[0] << endl << "Formula 2: " << outputs[1] << endl;
    return outputs;

}

int main(int argc, char* argv[])
{   
    vector<double> input;
 //   weights=read();
    if(argc == 1){
        input = { 0.1,0.2 };
        cout << "==============================================================" << endl << endl;
        cout << "Inputs: " << input[0] << ", " << input[1] << endl;
    }
    else{
        string a1 = argv[1];
        string a2 = argv[2];
        double a = stod(a1);
        double b = stod(a2);
        //cout << a << endl;
        //cout << b;
        input.push_back(a);
        input.push_back(b);
        cout << endl << "==============================================================" << endl << endl;
        cout << "Inputs: " << input[0] << ", " << input[1] << endl;
        //Condition to stop from infinite runs
        if(a > 1.0 || b > 1.0){
            return 1;
        }
    }

    
    vector<int> read_fds, write_fds;

    // Create pipes for each layer
    for (int i = 0; i <= weights.size(); i++) {
        int fds[2];
        if (pipe(fds) != 0) {
            cerr << "Failed to create pipe\n";
            exit(1);
        }
        read_fds.push_back(fds[0]);
        write_fds.push_back(fds[1]);
    }
//First layer hardcoded in main process
    
    vector<double> output_neurons(weights[0][0].size());
    vector<double> input_neurons(weights[0][0].size());
    
    write(write_fds[0], input.data(), sizeof(double) * input.size());
    // Fork a new process for each layer
    for (int i = 0; i < weights.size(); i++) 
    {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process - compute layer
            compute_middle_layers(i, read_fds[i], write_fds[i+1]);
            if(i == 6){
                vector<double> new_outputs(1);
                read(read_fds[i+1], new_outputs.data(), sizeof(double) * new_outputs.size());
                new_outputs = generate_newoutputs(new_outputs[0]);
                //cout << new_outputs[0] << endl << new_outputs[1];
                for(int c = weights.size()-1;c >= 1;c--){
                    write(write_fds[c], new_outputs.data(), sizeof(double) * new_outputs.size());
                    read(read_fds[c], new_outputs.data(), sizeof(double) * new_outputs.size());
                    cout << "\n_______________Backtrack of layer "<< c <<"___________________________\n";
                    cout << new_outputs[0] << " " << new_outputs[1] << endl;
                    if(c==1){
                        write(write_fds[0], new_outputs.data(), sizeof(double) * new_outputs.size());
                    }
                }
                
            }
            exit(0);
        } 
        else {
            // Parent process - continue forking
            //usleep(1000000);
        }
    }
    // Read output from the last layer
    read(read_fds[0], input.data(), sizeof(double) * input.size());
    string arg1 = to_string(input[0]);
    string arg2 = to_string(input[1]);
    char* a1 = strcpy(new char[arg1.length() + 1], arg1.c_str());
    char* a2 = strcpy(new char[arg2.length() + 1], arg2.c_str());
 
    char *args[]={"./c",a1,a2};
    execvp(args[0],args);
    
    
} 
