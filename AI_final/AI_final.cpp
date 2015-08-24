//// AI_final.cpp : Defines the entry point for the console application.
////
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <sstream>
#include "GA_Player.h"
#include <algorithm>

#include "opencv2/core/core.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/legacy/legacy.hpp"

using namespace std;
//VARIABLES for CODEBOOK METHOD:
CvBGCodeBookModel* model = 0;
const int NCHANNELS = 3;
int a = 10;
bool ch[NCHANNELS] = { true, true, true }; // This sets what channels should be adjusted for background bounds
bool getvalue = true;

int trace();
int detect(IplImage* img_8uc1, IplImage* img_8uc3);

void help(void)
{
	printf("\nLearn background and find foreground using simple average and average difference learning method:\n"
		"\nUSAGE:\nbgfg_codebook [--nframes=300] [movie filename, else from camera]\n"
		"***Keep the focus on the video windows, NOT the consol***\n\n"
		"INTERACTIVE PARAMETERS:\n"
		"\tESC,q,Q  - quit the program\n"
		"\th	- print this help\n"
		"\tp	- pause toggle\n"
		"\ts	- single step\n"
		"\tr	- run mode (single step off)\n"
		"=== AVG PARAMS ===\n"
		"\t-    - bump high threshold UP by 0.25\n"
		"\t=    - bump high threshold DOWN by 0.25\n"
		"\t[    - bump low threshold UP by 0.25\n"
		"\t]    - bump low threshold DOWN by 0.25\n"
		"=== CODEBOOK PARAMS ===\n"
		"\ty,u,v- only adjust channel 0(y) or 1(u) or 2(v) respectively\n"
		"\ta	- adjust all 3 channels at once\n"
		"\tb	- adjust both 2 and 3 at once\n"
		"\ti,o	- bump upper threshold up,down by 1\n"
		"\tk,l	- bump lower threshold up,down by 1\n"
		"\tSPACE - reset the model\n"
		);
}

//
//USAGE:  ch9_background startFrameCollection# endFrameCollection# [movie filename, else from camera]
//If from AVI, then optionally add HighAvg, LowAvg, HighCB_Y LowCB_Y HighCB_U LowCB_U HighCB_V LowCB_V
//
int main(int argc, char** argv)
{
	int get_result;
	int o_Player, o_Player_winCount = 0;
	int win_combination[3] = { 0, 0, 0 };
	int r_Player, r_Player_winCount = 0;
	int fitness_value = 0, base_10 = 0, parser = 0;
	static int population_counter = 0;
	int temp = 0, temp_parser, trace_array[population_size];
	int *max, *min, avg;
	Player GA_Player[10];
	int baseVal, baseCaprice, index[elite_pop];
	float alpha = 0.005f, pCaprice = 0.0f;
	//get_result = trace();

	for (int i = 0; i < Game_Course; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			r_Player = rand() % 3;
			o_Player = rand() % 3;
			//std::cout << "Parser : " << parser << endl;
			if (r_Player == ROCK && o_Player == ROCK || r_Player == PAPER && o_Player == PAPER || r_Player == SCISSORS && o_Player == SCISSORS)
			{
				

				if (parser == 0)
				{
					//std::cout << " input : "<< r_Player<<" parser : " << parser<< endl;
					temp = 9;
					temp = r_Player*temp;
					base_10 += temp;
					win_combination[parser + 2] = r_Player;

					//std::cout << "base : " << base_10 << endl;

				}
				else if (parser == 1)
				{
					//std::cout << " input : " << r_Player << " parser : " << parser << endl;
					temp = 3;
					temp = r_Player*temp;
					base_10 += temp;
					win_combination[parser] = r_Player;
					//std::cout << "base : " << base_10 << endl;
				}
				else if (parser == 2)
				{
					//std::cout << " input : " << r_Player << " parser : " << parser << endl;
					temp = 1;
					base_10 += r_Player;
					win_combination[parser - 2] = r_Player;
					//std::cout << "base : " << base_10 << endl;
				}
				parser++;
			}
			else if (r_Player == PAPER && o_Player == ROCK || r_Player == ROCK && o_Player == SCISSORS || r_Player == SCISSORS && o_Player == PAPER)
			{
				

				r_Player_winCount += r_Player_winCount;
				if (parser == 0)
				{
					//std::cout << " input : " << r_Player << " parser : " << parser << endl;
					temp = 9;
					temp = r_Player*temp;
					base_10 += temp;
					win_combination[parser + 2] = r_Player;
					//std::cout << "base : " << base_10 << endl;

				}
				else if (parser == 1)
				{
					//std::cout << " input : " << r_Player << " parser : " << parser << endl;
					temp = 3;
					temp = r_Player*temp;
					base_10 += temp;
					win_combination[parser] = r_Player;
					//std::cout << "base : " << base_10 << endl;
				}
				else if (parser == 2)
				{
					//std::cout << " input : " << r_Player << " parser : " << parser << endl;
					temp = 1;
					base_10 += r_Player;
					win_combination[parser - 2] = r_Player;
					//std::cout << "base : " << base_10 << endl;
				}
				parser++;
			}
			else if (o_Player == PAPER && r_Player == ROCK || o_Player == ROCK && r_Player == SCISSORS || o_Player == SCISSORS && r_Player == PAPER)
			{
				
				o_Player_winCount += o_Player_winCount;
				if (parser == 0)
				{
					//std::cout << " input : " << o_Player << " parser : " << parser << endl;
					temp = 9;
					temp = o_Player*temp;
					base_10 += temp;
					win_combination[parser + 2] = o_Player;
					//std::cout << "base : " << base_10 << endl;

				}
				else if (parser == 1)
				{
					//std::cout << " input : " << o_Player << " parser : " << parser << endl;
					temp = 3;
					temp = o_Player*temp;
					base_10 += temp;
					win_combination[parser] = o_Player;
					//std::cout << "base : " << base_10 << endl;
				}
				else if (parser == 2)
				{
					//std::cout << " input : " << o_Player << " parser : " << parser << endl;
					temp = 1;
					base_10 += o_Player;
					win_combination[parser - 2] = o_Player;

					/*std::cout << "base : " << base_10 << endl;*/
				}
				parser++;
			}
			temp_parser = parser - 1;
			//updation of GA chromosomes with winning probablity
			for (int h = 0; h < population_size; h++)
			{
				//cout << "Chromosome :" << endl;
				//cout << GA_Player[h].chromosome[31] << " : " << GA_Player[h].chromosome[32] << " : " << GA_Player[h].chromosome[33] << endl;
				baseVal = GA_Player[h].chromosome[31] * 9;
				baseVal += GA_Player[h].chromosome[32] * 3;
				baseVal += GA_Player[h].chromosome[33] * 1;
				//	cout << "Base Val : " << baseVal << endl;

				//Caprice calculation
				baseCaprice = GA_Player[h].chromosome[27] * 18;
				baseCaprice += GA_Player[h].chromosome[28] * 9;
				baseCaprice += GA_Player[h].chromosome[29] * 3;
				baseCaprice += GA_Player[h].chromosome[30] * 1;

				pCaprice = baseCaprice*alpha;
				if (pCaprice > 0.3)
				{
					//cout << "pcaprice : " << pCaprice << endl;
					GA_Player[h].chromosome[baseVal] = rand() % 3;
				}

				//GA_Player[h].chromosome[baseVal];
				if (GA_Player[h].chromosome[baseVal] == PAPER && win_combination[temp_parser] == ROCK || GA_Player[h].chromosome[baseVal] == ROCK && win_combination[temp_parser] == SCISSORS || GA_Player[h].chromosome[baseVal] == SCISSORS && win_combination[temp_parser] == PAPER)
				{
					trace_array[h] = ++GA_Player[h].fitness_value;
				}
				GA_Player[h].chromosome[27] = GA_Player[h].chromosome[28];
				GA_Player[h].chromosome[28] = GA_Player[h].chromosome[29];
				GA_Player[h].chromosome[29] = GA_Player[h].chromosome[30];
				GA_Player[h].chromosome[30] = GA_Player[h].chromosome[31];
				GA_Player[h].chromosome[31] = GA_Player[h].chromosome[32];
				GA_Player[h].chromosome[32] = GA_Player[h].chromosome[33];
				GA_Player[h].chromosome[33] = win_combination[temp_parser];
				//	cout << "After :"<<endl<<GA_Player[h].chromosome[31] << " : " << GA_Player[h].chromosome[32] << " : " << GA_Player[h].chromosome[33] << endl;
			}

		}
		//	 std::cout << endl << "Base value : " << base_10 << endl;


		//	input_value = stringstream();
		//std::cout << "input : " << input;
		//istringstream(input) >> fitness_value;
		//for (int h = 0; h < 3; h++)
		//			std::cout << ": "<< win_combination[h];

		temp = 0;
		parser = 0;
		base_10 = 0;
	}

	max = std::max_element(trace_array, trace_array + population_size);
	//min = min_element(trace_array, trace_array + population_size);
	//cout << "max :" << *max << endl;
	//cout << "min : " << *min << endl;
	//avg = ((*min) + (*max)) / 2;
	//cout << "average : " << avg << endl;
	int elite_num = 0, next = 0;
	while (elite_num<5)
	{
		if (trace_array[next] == *max)
		{
			//cout << "Next : " << next<<endl;
			index[elite_num] = next;
			elite_num++;
			trace_array[next] = 0;
			next = 0;
			max = std::max_element(trace_array, trace_array + population_size);
		}
		else
		{
			next++;
		}
	}

	/*for (int h = 0; h < population_size; h++)
	{
	for (int j = 0; j < chromosome_size; j++)
	{
	cout << GA_Player[h].chromosome[j];

	}
	cout << endl;
	}*/
	//cout << "**************************" << endl;
	elite_num = 0;
	int step = 0;
	for (int h = 0; h < population_size; h++)
	{
		if (!(std::find(std::begin(index), std::end(index), h) != std::end(index)))
		{
			if (step < 2)
			{
				//cout << "H: " << h << endl;
				for (int j = 0; j < 13; j++)
				{
					//	cout << "j : " << j << " : " << j + 13 << endl;
					//cout << "H: " << h << " GA_Player[index[elite_num]].chromosome[j] : " << GA_Player[index[elite_num]].chromosome[j] << endl;
					elite_num %= 5;
					GA_Player[h].chromosome[j] = GA_Player[index[elite_num]].chromosome[j];
					GA_Player[h].chromosome[j + 13] = GA_Player[index[elite_num + 1]].chromosome[j + 13];
					int mutate = rand() % 3;
					if (mutate == 2)
					{
						GA_Player[h].chromosome[j] = (GA_Player[h].chromosome[j] + 2) % 3;
					}

				}
				//cout << "Elite_num after crossover: " << elite_num << endl;
				elite_num += 1;
				step++;
			}
			else
			{
				elite_num = 1;
				step = 0;
			}
		}
	}

	int Generation = 0;
	for (;;)
	{
		for (int h = 0; h < population_size; h++)
		{
			//Re initialising variables
			GA_Player[h].fitness_value = 0;
			trace_array[h] = 0;
		}

		cout << endl << "Generation : " << ++Generation << endl;
		for (int i = 0; i < Game_Course; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				/*cout << "Press k to continue : "<<endl;
				if ((_getch() == 'k'))
				{
				cout << "Enter your choice : ";
				cin >> o_Player;
				}*/
				//o_Player = 1;
				if (getvalue == true)
				{
					getvalue = false;
					o_Player = trace();
					if (o_Player >= 5)
					{
						o_Player = PAPER;
						cout << "Player : PAPER" ;
					}
					else if (o_Player >= 2 || o_Player <5)
					{
						o_Player = SCISSORS;
						cout << "Player : SCISSORS" ;
					}
					else if (o_Player >= 0 || o_Player <2)
					{
						o_Player = ROCK;
						cout << "Player : ROCK";
					}
					else
					{
						cout << "Player : " << o_Player;
						cout << "Enter proper value" << endl;
						o_Player = 0;
					}
				}
				
				baseVal = GA_Player[index[0]].chromosome[31] * 9;
				baseVal += GA_Player[index[0]].chromosome[32] * 3;
				baseVal += GA_Player[index[0]].chromosome[33] * 1;

				//Caprice calculation
				baseCaprice = GA_Player[index[0]].chromosome[27] * 18;
				baseCaprice += GA_Player[index[0]].chromosome[28] * 9;
				baseCaprice += GA_Player[index[0]].chromosome[29] * 3;
				baseCaprice += GA_Player[index[0]].chromosome[30] * 1;

				pCaprice = baseCaprice*alpha*GA_Player[index[0]].lamda;
				if (pCaprice > 0.3)
				{
					//cout << "pcaprice : " << pCaprice << endl;
					GA_Player[index[0]].chromosome[baseVal] = rand() % 3;
				}
				
				cout << "  Computer : " << GA_Player[index[0]].chromosome[baseVal] << endl;


				if (GA_Player[index[0]].chromosome[baseVal] == 1)
				{
					cout << "Computer : PAPER";
				}
				else if (GA_Player[index[0]].chromosome[baseVal] == 0)
				{
					cout << "Computer : SCISSORS";
				}
				else if (GA_Player[index[0]].chromosome[baseVal] == 2)
				{
					cout << "Computer : ROCK";
				}
				


				if (GA_Player[index[0]].chromosome[baseVal] == ROCK && o_Player == ROCK || GA_Player[index[0]].chromosome[baseVal] == PAPER && o_Player == PAPER || GA_Player[index[0]].chromosome[baseVal] == SCISSORS && o_Player == SCISSORS)
				{
					cout << "Draw" << endl;
					GA_Player[index[0]].lamda = 0;


				}
				else if (GA_Player[index[0]].chromosome[baseVal] == PAPER && o_Player == ROCK || GA_Player[index[0]].chromosome[baseVal] == ROCK && o_Player == SCISSORS || GA_Player[index[0]].chromosome[baseVal] == SCISSORS && o_Player == PAPER)
				{
					cout << "Computer Wins " << endl;
					trace_array[index[0]] = ++GA_Player[index[0]].fitness_value;
					GA_Player[index[0]].lamda = 0;
				}
				else if (o_Player == PAPER && GA_Player[index[0]].chromosome[baseVal] == ROCK || o_Player == ROCK && GA_Player[index[0]].chromosome[baseVal] == SCISSORS || o_Player == SCISSORS && GA_Player[index[0]].chromosome[baseVal] == PAPER)
				{
					cout << "You won " << endl;
					GA_Player[index[0]].lamda++;
				}

				GA_Player[index[0]].chromosome[27] = GA_Player[index[0]].chromosome[28];
				GA_Player[index[0]].chromosome[28] = GA_Player[index[0]].chromosome[29];
				GA_Player[index[0]].chromosome[29] = GA_Player[index[0]].chromosome[30];
				GA_Player[index[0]].chromosome[30] = GA_Player[index[0]].chromosome[31];
				GA_Player[index[0]].chromosome[31] = GA_Player[index[0]].chromosome[32];
				GA_Player[index[0]].chromosome[32] = GA_Player[index[0]].chromosome[33];
				GA_Player[index[0]].chromosome[33] = o_Player;


				//updation of GA chromosomes with winning probablity
				for (int h = 0; h < population_size; h++)
				{
					if (h != index[0])
					{

						//cout << "Chromosome :" << endl;
						//cout << GA_Player[h].chromosome[31] << " : " << GA_Player[h].chromosome[32] << " : " << GA_Player[h].chromosome[33] << endl;
						baseVal = GA_Player[h].chromosome[31] * 9;
						baseVal += GA_Player[h].chromosome[32] * 3;
						baseVal += GA_Player[h].chromosome[33] * 1;
						//	cout << "Base Val : " << baseVal << endl;

						//Caprice calculation
						baseCaprice = GA_Player[h].chromosome[27] * 18;
						baseCaprice += GA_Player[h].chromosome[28] * 9;
						baseCaprice += GA_Player[h].chromosome[29] * 3;
						baseCaprice += GA_Player[h].chromosome[30] * 1;

						pCaprice = baseCaprice*alpha*GA_Player[h].lamda;
						if (pCaprice > 0.3)
						{
							//cout << "pcaprice : " << pCaprice << endl;
							GA_Player[h].chromosome[baseVal] = rand() % 3;
						}

						//GA_Player[h].chromosome[baseVal];
						if (GA_Player[h].chromosome[baseVal] == PAPER && o_Player == ROCK || GA_Player[h].chromosome[baseVal] == ROCK && o_Player == SCISSORS || GA_Player[h].chromosome[baseVal] == SCISSORS && o_Player == PAPER)
						{
							trace_array[h] = ++GA_Player[h].fitness_value;
						}
						else
						{
							GA_Player[h].lamda++;
						}
						GA_Player[h].chromosome[27] = GA_Player[h].chromosome[28];
						GA_Player[h].chromosome[28] = GA_Player[h].chromosome[29];
						GA_Player[h].chromosome[29] = GA_Player[h].chromosome[30];
						GA_Player[h].chromosome[30] = GA_Player[h].chromosome[31];
						GA_Player[h].chromosome[31] = GA_Player[h].chromosome[32];
						GA_Player[h].chromosome[32] = GA_Player[h].chromosome[33];
						GA_Player[h].chromosome[33] = o_Player;
						//	cout << "After :"<<endl<<GA_Player[h].chromosome[31] << " : " << GA_Player[h].chromosome[32] << " : " << GA_Player[h].chromosome[33] << endl;
					}
				}


			}

		}

		for (int h = 0; h < population_size; h++)
		{
			//cout << "Trace array : " << trace_array[h] << endl;

			for (int j = 0; j < chromosome_size; j++)
			{
				//cout << GA_Player[h].chromosome[j];

			}
			//cout << endl;e
			cout << " H : " << h << " fitness : " << GA_Player[h].fitness_value << endl;

		}

		max = max_element(trace_array, trace_array + population_size);
		elite_num = 0, next = 0;
		while (elite_num < 5)
		{
			if (trace_array[next] == *max)
			{
				cout << "Next : " << next << endl;
				index[elite_num] = next;
				elite_num++;
				trace_array[next] = 0;
				next = 0;
				max = max_element(trace_array, trace_array + population_size);
			}
			else
			{
				next++;
			}
		}

		/*for (int h = 0; h < population_size; h++)
		{
		for (int j = 0; j < chromosome_size; j++)
		{
		cout << GA_Player[h].chromosome[j];

		}
		cout << endl;
		}
		cout << "#######################" << endl;*/

		elite_num = 0;
		step = 0;
		for (int h = 0; h < population_size; h++)
		{
			if (!(find(begin(index), end(index), h) != end(index)))
			{
				if (step < 2)
				{
					//cout << "H: " << h << endl;
					for (int j = 0; j < 13; j++)
					{
						//	cout << "j : " << j << " : " << j + 13 << endl;
						//cout << "H: " << h << " GA_Player[index[elite_num]].chromosome[j] : " << GA_Player[index[elite_num]].chromosome[j] << endl;
						elite_num %= 5;
						GA_Player[h].chromosome[j] = GA_Player[index[elite_num]].chromosome[j];
						GA_Player[h].chromosome[j + 13] = GA_Player[index[elite_num + 1]].chromosome[j + 13];
						int mutate = rand() % 3;
						if (mutate == 2)
						{
							GA_Player[h].chromosome[j] = (GA_Player[h].chromosome[j] + 2) % 3;
						}

					}
					//cout << "Elite_num after crossover: " << elite_num << endl;
					elite_num += 1;
					step++;
				}
				else
				{
					elite_num = 1;
					step = 0;
				}
			}
		}

		for (int h = 0; h < population_size; h++)
		{
			for (int j = 0; j < chromosome_size; j++)
			{
				//cout << GA_Player[h].chromosome[j];

			}
			//cout << endl;
		}

		cout << "Press e to continue : ";
		if (!(_getch() == 'e'))
		{
			getvalue = true;
			break;
		}
		else
		{
			getvalue = false;
		}
	}
	_getch();
	
	return 0;
}


int trace()
{

	IplImage* rawImage = 0, *yuvImage = 0; //yuvImage is for codebook method
	IplImage *ImaskCodeBook = 0, *ImaskCodeBookCC = 0;
	CvCapture* capture = 0;

	int c, n, nframes = 0;
	int nframesToLearnBG = 300;
	int inputvalue = 0;

	model = cvCreateBGCodeBookModel();

	//Set color thresholds to default values
	model->modMin[0] = 3;
	model->modMin[1] = model->modMin[2] = 3;
	model->modMax[0] = 10;
	model->modMax[1] = model->modMax[2] = 10;
	model->cbBounds[0] = model->cbBounds[1] = model->cbBounds[2] = 10;

	bool pause = false;
	bool singlestep = false;

	capture = cvCaptureFromCAM(0);
	

	if (!capture)
	{
		printf("Can not initialize video capturing\n\n");
		help();
		return -1;
	}

	//MAIN PROCESSING LOOP:
	for (;;)
	{
		if (!pause)
		{
			rawImage = cvQueryFrame(capture);
			++nframes;
			if (!rawImage)
				break;
		}
		if (singlestep)
			pause = true;

		//First time:
		if (nframes == 1 && rawImage)
		{
			// CODEBOOK METHOD ALLOCATION
			yuvImage = cvCloneImage(rawImage);
			ImaskCodeBook = cvCreateImage(cvGetSize(rawImage), IPL_DEPTH_8U, 1);
			ImaskCodeBookCC = cvCreateImage(cvGetSize(rawImage), IPL_DEPTH_8U, 1);
			cvSet(ImaskCodeBook, cvScalar(255));

			cvNamedWindow("Raw", 1);
			cvNamedWindow("ForegroundCodeBook", 1);
			cvNamedWindow("CodeBook_ConnectComp", 1);
		}

		// If we've got an rawImage and are good to go:
		if (rawImage)
		{
			cvCvtColor(rawImage, yuvImage, CV_BGR2YCrCb);//YUV For codebook method
			//This is where we build our background model
			if (!pause && nframes - 1 < nframesToLearnBG)
				cvBGCodeBookUpdate(model, yuvImage);

			if (nframes - 1 == nframesToLearnBG)
				cvBGCodeBookClearStale(model, model->t / 2);

			//Find the foreground if any
			if (nframes - 1 >= nframesToLearnBG)
			{
				// Find foreground by codebook method
				cvBGCodeBookDiff(model, yuvImage, ImaskCodeBook);
				// This part just to visualize bounding boxes and centers if desired
				cvCopy(ImaskCodeBook, ImaskCodeBookCC);
				cvSegmentFGMask(ImaskCodeBookCC);
				//bwareaopen_(ImaskCodeBookCC,100);
				cvShowImage("CodeBook_ConnectComp", ImaskCodeBookCC);
				inputvalue=detect(ImaskCodeBookCC, rawImage);
				if (getvalue == true)
				{
					break;
				}
			}
			//Display
			cvShowImage("Raw", rawImage);
			cvShowImage("ForegroundCodeBook", ImaskCodeBook);

		}

		// User input:
		c = cvWaitKey(10) & 0xFF;
		c = tolower(c);
		// End processing on ESC, q or Q
		if (c == 27 || c == 'q')
			break;
		//Else check for user input
		switch (c)
		{
		case 'h':
			help();
			break;
		case 'p':
			pause = !pause;
			break;
		case 's':
			singlestep = !singlestep;
			pause = false;
			break;
		case 'r':
			pause = false;
			singlestep = false;
			break;
		case ' ':
			cvBGCodeBookClearStale(model, 0);
			nframes = 0;
			break;
			//CODEBOOK PARAMS
		case 'y': case '0':
		case 'u': case '1':
		case 'v': case '2':
		case 'a': case '3':
		case 'b':
			ch[0] = c == 'y' || c == '0' || c == 'a' || c == '3';
			ch[1] = c == 'u' || c == '1' || c == 'a' || c == '3' || c == 'b';
			ch[2] = c == 'v' || c == '2' || c == 'a' || c == '3' || c == 'b';
			//printf("CodeBook YUV Channels active: %d, %d, %d\n", ch[0], ch[1], ch[2]);
			break;
		case 'i': //modify max classification bounds (max bound goes higher)
		case 'o': //modify max classification bounds (max bound goes lower)
		case 'k': //modify min classification bounds (min bound goes lower)
		case 'l': //modify min classification bounds (min bound goes higher)
		{
					  uchar* ptr = c == 'i' || c == 'o' ? model->modMax : model->modMin;
					  for (n = 0; n<NCHANNELS; n++)
					  {
						  if (ch[n])
						  {
							  int v = ptr[n] + (c == 'i' || c == 'l' ? 1 : -1);
							  ptr[n] = cv::saturate_cast<uchar>(v);
						  }
					//	  printf("%d,", ptr[n]);
					  }
					//  printf(" CodeBook %s Side\n", c == 'i' || c == 'o' ? "High" : "Low");
		}
			break;
		}
		
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("Raw");
	cvDestroyWindow("ForegroundCodeBook");
	cvDestroyWindow("CodeBook_ConnectComp");
	
	return inputvalue;
}

int detect(IplImage* img_8uc1, IplImage* img_8uc3) {


	//cvNamedWindow( "aug", 1 );


	//cvThreshold( img_8uc1, img_edge, 128, 255, CV_THRESH_BINARY );
	CvMemStorage* storage = cvCreateMemStorage();
	char txt[] = "0";
	CvSeq* first_contour = NULL;
	CvSeq* maxitem = NULL;
	double area = 0, areamax = 0;
	int maxn = 0;
	int Nc = cvFindContours(
		img_8uc1,
		storage,
		&first_contour,
		sizeof(CvContour),
		CV_RETR_LIST // Try all four values and see what happens
		);
	int n = 0;
	//printf( "Total Contours Detected: %d\n", Nc );

	if (Nc>0)
	{
		for (CvSeq* c = first_contour; c != NULL; c = c->h_next)
		{

			//cvCvtColor( img_8uc1, img_8uc3, CV_GRAY2BGR );

			area = cvContourArea(c, CV_WHOLE_SEQ);

			if (area>areamax)
			{
				areamax = area;
				maxitem = c;
				maxn = n;
			}



			n++;


		}
		CvMemStorage* storage3 = cvCreateMemStorage(0);
		//if (maxitem) maxitem = cvApproxPoly( maxitem, sizeof(maxitem), storage3, CV_POLY_APPROX_DP, 3, 1 );



		if (areamax>5000)
		{
			maxitem = cvApproxPoly(maxitem, sizeof(CvContour), storage3, CV_POLY_APPROX_DP, 10, 1);

			CvPoint pt0;

			CvMemStorage* storage1 = cvCreateMemStorage(0);
			CvMemStorage* storage2 = cvCreateMemStorage(0);
			CvSeq* ptseq = cvCreateSeq(CV_SEQ_KIND_GENERIC | CV_32SC2, sizeof(CvContour),
				sizeof(CvPoint), storage1);
			CvSeq* hull;
			CvSeq* defects;

			for (int i = 0; i < maxitem->total; i++)
			{
				CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, maxitem, i);
				pt0.x = p->x;
				pt0.y = p->y;
				cvSeqPush(ptseq, &pt0);
			}
			hull = cvConvexHull2(ptseq, 0, CV_CLOCKWISE, 0);
			int hullcount = hull->total;

			defects = cvConvexityDefects(ptseq, hull, storage2);

			//printf(" defect no %d \n",defects->total);




			CvConvexityDefect* defectArray;


			int j = 0, k=0;
			//int m_nomdef=0;
			// This cycle marks all defects of convexity of current contours.
			for (; defects; defects = defects->h_next)
			{
				a--;
				int nomdef = defects->total; // defect amount
				//outlet_float( m_nomdef, nomdef );

				//printf(" defect no %d \n",nomdef);
				
				if (nomdef == 0)
					continue;

				// Alloc memory for defect set.
				//fprintf(stderr,"malloc\n");
				defectArray = (CvConvexityDefect*)malloc(sizeof(CvConvexityDefect)*nomdef);

				// Get defect set.
				//fprintf(stderr,"cvCvtSeqToArray\n");
				cvCvtSeqToArray(defects, defectArray, CV_WHOLE_SEQ);

				// Draw marks for all defects.
				for (int i = 0; i<nomdef; i++)
				{
					//printf(" defect depth for defect %d %f \n", i, defectArray[i].depth);
					cvLine(img_8uc3, *(defectArray[i].start), *(defectArray[i].depth_point), CV_RGB(255, 255, 0), 1, CV_AA, 0);
					cvCircle(img_8uc3, *(defectArray[i].depth_point), 5, CV_RGB(0, 0, 164), 2, 8, 0);
					cvCircle(img_8uc3, *(defectArray[i].start), 5, CV_RGB(0, 0, 164), 2, 8, 0);
					cvLine(img_8uc3, *(defectArray[i].depth_point), *(defectArray[i].end), CV_RGB(255, 255, 0), 1, CV_AA, 0);

				}
				
				char txt[] = "0";
				txt[0] = '0' + nomdef - 1;
				CvFont font;
				cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 5, CV_AA);
				k = atoi(txt);
				cvPutText(img_8uc3, txt, cvPoint(50, 50), &font, cvScalar(0, 0, 255, 0));
				
				j++;
				
				// Free memory.
				free(defectArray);
				cout << "Show input in :  " << a << endl;
				if (a<=0)
				{
					a = 10;
					getvalue = true;
					cout << "K: " << k;
					return k;
				}
			}


			cvReleaseMemStorage(&storage);
			cvReleaseMemStorage(&storage1);
			cvReleaseMemStorage(&storage2);
			cvReleaseMemStorage(&storage3);
			return k;
			//return 0;
		}
	}
}
