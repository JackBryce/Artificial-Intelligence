#include "ArtificialIntelligence.h";
#include <random>;
#include <bitset>;
#include <string>;
#include <iostream>;
#include <fstream>;
#include <windows.h>;

using namespace std;

//This constructor runs the Artificial Intelligence.
ArtificialIntelligence::ArtificialIntelligence(int count) {
	id = bitset<8>(count).to_string();
	updatedKey = id;
	setupAI();
	//thread(Thread); //C1189 error
}

void ArtificialIntelligence::Thread() {
	int dataSetCount = 0;
	vector<WCHAR*> files;
	vector<WCHAR*> newFiles;

	//Load the files into the vector for the initial files.
	WIN32_FIND_DATA fd;
	HANDLE audio = FindFirstFile((LPCWSTR)".mp3", &fd);
	HANDLE image = FindFirstFile((LPCWSTR)".png", &fd);
	HANDLE text = FindFirstFile((LPCWSTR)"*.txt", &fd);
	HANDLE video = FindFirstFile((LPCWSTR)"*.avi", &fd);
	int counter = 0;
	int pointOne = 0;
	int pointTwo = 0;
	int pointThree = 0;
	int pointFour = 0;

	if (audio != INVALID_HANDLE_VALUE) {
		do {
			newFiles.push_back(fd.cFileName);
			counter += 1;
		} while (FindNextFile(audio, &fd));
	} else if (image != INVALID_HANDLE_VALUE) {
		pointOne = counter;
		do {
			newFiles.push_back(fd.cFileName);
			counter += 1;
		} while (FindNextFile(image, &fd));
	} else if (text != INVALID_HANDLE_VALUE) {
		pointTwo = counter;
		do {
			newFiles.push_back(fd.cFileName);
			counter += 1;
		} while (FindNextFile(text, &fd));
		FindClose(text);
	} else if (video != INVALID_HANDLE_VALUE) {
		pointThree = counter;
		do {
			newFiles.push_back(fd.cFileName);
		} while (FindNextFile(video, &fd));
	}
	
	pointFour = counter;
	int initialSize = files.size();
	int count = files.size();

	//This runs the Artificial Intelligence until told otherwise.
	while (updatedKey == id) {
		/* --- Check for new data files for DynamicNetworkGenerator's text RNN, video/image CNN to build the network. --- */
		if (audio != INVALID_HANDLE_VALUE) {
			do {
				newFiles.push_back(fd.cFileName);
				counter += 1;
			} while (FindNextFile(audio, &fd));
		} else if (image != INVALID_HANDLE_VALUE) {
			pointOne = counter;
			do {
				newFiles.push_back(fd.cFileName);
				counter += 1;
			} while (FindNextFile(image, &fd));
		} else if (text != INVALID_HANDLE_VALUE) {
			pointTwo = counter;
			do {
				newFiles.push_back(fd.cFileName);
				counter += 1;
			} while (FindNextFile(text, &fd));
			FindClose(text);
		} else if (video != INVALID_HANDLE_VALUE) {
			pointThree = counter;
			do {
				newFiles.push_back(fd.cFileName);
			} while (FindNextFile(video, &fd));
		}
		count = newFiles.size();

		//This generates Neural Networks for the AI or runs the data through the Neural network in the situation that there is new files.
		if ((initialSize - count) < 0) {
			files = newFiles;
			newFiles.empty();

			/* --- Run data from section above through the appropriate Neural Network to generate a network if required. --- */
			for (int i = 0; i < files.size(); i++) {
				string line;
				ifstream fileInput;
				fileInput.open(files[i], ios::binary);

				int n = 1;
				int counting = 0;
				double count = 0.0;

				vector<double> audioData;
				vector<string> imageDataSub;
				vector<vector<double>> imageData;
				vector<double> textData;
				vector<string> videoDataSub;
				vector<vector<double>> videoData;
				if (i <= pointOne) {
					while (getline(fileInput, line)) {
						for (int j = line.size(); j >= 0; j--) {
							if (line[j] == '1') {
								count += n;
							}

							n *= 2;
						}
						n = 1;

						while (count > 0) {
							count /= 10;
						}
						audioData.push_back(count);
					}
				} else if (i > pointOne && i <= pointTwo) {
					while (getline(fileInput, line)) {
						if (counting == 2) {
							imageDataSub.push_back(line);

							vector<double> colour;
							for (int j = 0; j < imageDataSub.size(); j++) {
								for (int k = imageDataSub[j].size(); k >= 0; k--) {
									if (line[j] == '1') {
										count += n;
									}

									n *= 2;
								}
								n = 1;

								while (count > 0) {
									count /= 10;
								}
								colour.push_back(count);
							}
							imageData.push_back(colour);
						} else {
							imageDataSub.push_back(line);
							counting += 1;
						}
					}
				} else if (i > pointTwo && i <= pointThree) {
					while (getline(fileInput, line)) {
						for (int j = line.size(); j >= 0; j--) {
							if (line[j] == '1') {
								count += n;
							}

							n *= 2;
						}
						n = 1;

						while (count < 0) {
							count /= 10;
						}
						textData.push_back(count);
					}
				} else {
					while (getline(fileInput, line)) {
						if (counting == 2) {
							videoDataSub.push_back(line);

							vector<double> colour;
							for (int j = 0; j < videoDataSub.size(); j++) {
								for (int k = videoDataSub[j].size(); k >= 0; k--) {
									if (line[j] == '1') {
										count += n;
									}

									n *= 2;
								}
								n = 1;

								while (count > 0) {
									count /= 10;
								}
								colour.push_back(count);
							}
							videoData.push_back(colour);
						} else {
							videoDataSub.push_back(line);
							counting += 1;
						}
					}
				}

				/* --- Feed the appropriate data files into the appropriate existing neural network if required and fetch any appropriate data from the Core's memory matrix. --- */
				for (int i = 0; i < textData.size(); i++) {
					if (i <= pointOne) {
						_audioNetwork->feedFoward(audioData);

						/* --- Store the output data from the neural networks above into the AI's Core's memory matrix if required. --- */
						if (dataSetCount <= 65536) {
							DataSet *ds = new DataSet();
							ds->id = bitset<16>(dataSetCount).to_string();
							ds->memoryMatrixInputS = audioData;
							ds->memoryMatrixOutput = _audioNetwork->output;

							dataSets.push_back(ds);
							dataSetCount += 1;
						}
					} else if (i > pointOne && i <= pointTwo) {
						for (int j = 0; j < imageData.size(); j++) {
							_imageNetwork->feedFoward(imageData[j]);
						}

						/* --- Store the output data from the neural networks above into the AI's Core's memory matrix if required. --- */
						if (dataSetCount <= 65536) {
							DataSet *ds = new DataSet();
							ds->id = bitset<16>(dataSetCount).to_string();
							ds->memoryMatrixInputL = imageData;
							ds->memoryMatrixOutput = _imageNetwork->output;

							dataSets.push_back(ds);
							dataSetCount += 1;
						}
					} else if (i > pointTwo && i <= pointThree) {
						_textNetwork->feedFoward(textData);

						/* --- Store the output data from the neural networks above into the AI's Core's memory matrix if required. --- */
						if (dataSetCount >= 65536) {
							DataSet *ds = new DataSet();
							ds->id = bitset<16>(dataSetCount).to_string();
							ds->memoryMatrixInputS = textData;
							ds->memoryMatrixOutput = _textNetwork->output;

							dataSets.push_back(ds);
							dataSetCount += 1;
						}
					} else {
						for (int j = 0; j < videoData.size(); j++) {
							_videoNetwork->feedFoward(videoData[j]);
						}

						/* --- Store the output data from the neural networks above into the AI's Core's memory matrix if required. --- */
						if (dataSetCount <= 65536) {
							DataSet *ds = new DataSet();
							ds->id = bitset<16>(dataSetCount).to_string();
							ds->memoryMatrixInputL = videoData;
							ds->memoryMatrixOutput = _videoNetwork->output;

							dataSets.push_back(ds);
							dataSetCount += 1;
						}
					}
				} //The errors are in here for the 
				//dataSets.push_back(ds); is the error in the above for loop.
			}
		}

		vector<vector<vector<string>>> networkGenomes;
		/* --- Check on the performance of the neural networks. --- */
		for (int i = 0; i < networkDetails.size(); i++) {
			if (i <= pointOne) {
				networkGenomes.push_back(_audioNetwork->performance());
			} else if (i > pointOne && i <= pointTwo) {
				networkGenomes.push_back(_imageNetwork->performance());
			} else if (i > pointTwo && i <= pointThree) {
				networkGenomes.push_back(_textNetwork->performance());
			} else {
				networkGenomes.push_back(_videoNetwork->performance());
			}
		}

		//Run a fitness test on the networks.
		vector<vector<vector<int>>> fitnessScore;
		vector<vector<vector<string>>> Genomes;

		for (int i = 0; i < networkGenomes.size(); i++) {
			vector<vector<int>> fitnessScoreOne;
			vector<vector<string>> GenomesOne;
			for (int j = 0; j < networkGenomes[i].size(); j++) {
				vector<int> fitnessScoreTwo;
				vector<string> GenomesTwo;
				for (int k = 0; k < networkGenomes[i][j].size(); k++) {
					string genome = networkGenomes[i][j][k];
					int score = 0;
					for (int l = 0; l < genome.size(); l++) {
						switch (genome[l]) {
							case '1':
								score += 1;
								break;

							case '2':
								score += 1;
								break;

							
							case '3':
								score += 2;
								break;

							case '4':
								score += 1;
								break;

							case '5':
								score += 2;
								break;

							
							case '6':
								score += 2;
								break;

							case '7':
								score += 3;
								break;

							case '8':
								score += 1;
								break;

							case '9':
								score += 2;
								break;

							case 'A':
								score += 2;
								break;
						}
					}
					fitnessScoreTwo.push_back(score);
					GenomesTwo.push_back(genome);
				}
				fitnessScoreOne.push_back(fitnessScoreTwo);
				GenomesOne.push_back(GenomesTwo);
			}
			Genomes.push_back(GenomesOne);
			fitnessScore.push_back(fitnessScoreOne);
		}

		//Calculate the performance of the network.
		vector<int> change;
		vector<vector<double>> data;	//Network, Node.
		vector<vector<double>> targets; //Network, Target.
		vector<double> neuron;
		vector<double> neuronOne;
		double sum = 0.0;

		for (int i = 0; i < networkDetails.size(); i++) {
			neuron = data[i];

			for (int j = 0; j < networkDetails[i]->network->m_layer.size(); j++) {
				for (int k = 0; k < networkDetails[i]->network->m_layer[j].size(); k++) {
					if (networkDetails[i]->network->m_layer[j][k]->_ann == true) {
						for (int l = 0; l < neuron.size(); l++) {
							if (l == 0 && j == 0) {
								for (int m = 0; m < networkDetails[i]->network->m_layer[j][k]->ann->weightsFoward.size(); m++) {
									neuronOne.push_back(neuron[l] * networkDetails[i]->network->m_layer[j][k]->ann->weightsFoward[m].weight);
								}
							} else {
								for (int m = 0; m < networkDetails[i]->network->m_layer[j][k]->ann->weightsFoward.size(); m++) {
									neuronOne[m] += neuron[l] * networkDetails[i]->network->m_layer[j][k]->ann->weightsFoward[m].weight;
								}
							}
						}

						if (k++ == networkDetails[i]->network->m_layer[j].size()) {
							for (int l = 0; l < neuronOne.size(); l++) {
								neuronOne[l] = activationFunction(neuronOne[l]);
							}
							neuron = neuronOne;
							neuronOne.empty();
						}
					} else if (networkDetails[i]->network->m_layer[j][k]->_rnn == true) {
						for (int l = 0; l < neuron.size(); l++) {
							if (l == 0 && j == 0) {
								for (int m = 0; m < networkDetails[i]->network->m_layer[j][k]->rnn->weightsFoward.size(); m++) {
									neuronOne.push_back(neuron[l] * networkDetails[i]->network->m_layer[j][k]->rnn->weightsFoward[m].weight);
								}
							} else {
								for (int m = 0; m < networkDetails[i]->network->m_layer[j][k]->rnn->weightsFoward.size(); m++) {
									neuronOne[m] += neuron[l] * networkDetails[i]->network->m_layer[j][k]->rnn->weightsFoward[m].weight;
								}
							}
						}

						if (k++ == networkDetails[i]->network->m_layer[j].size()) {
							for (int l = 0; l < 2; l++) {
								for (int m = 0; m < neuronOne.size(); m++) {
									if (l == 0) {
										neuronOne[m] *= networkDetails[i]->network->m_layer[j][k]->rnn->weightsRecurrent[m].weight;
									} else {
										neuronOne[m] *= activationFunction(neuronOne[m]);
									}
								}

								if (l == 1) {
									neuron = neuronOne;
									neuronOne.empty();
								}
							}
						}
					} else if (networkDetails[i]->network->m_layer[j][k]->_lstm == true) {
						for (int l = 0; l < neuron.size(); l++) {
							if (l == 0 && j == 0) {
								for (int m = 0; m < networkDetails[i]->network->m_layer[j][k]->lstm->weightsFoward.size(); m++) {
									neuronOne.push_back(neuron[l]*networkDetails[i]->network->m_layer[j][k]->lstm->weightsFoward[m].weight);
								}
							} else {
								for (int m = 0; m < networkDetails[i]->network->m_layer[j][k]->lstm->weightsFoward.size(); m++) {
									neuron[m] += neuron[l]*networkDetails[i]->network->m_layer[j][k]->lstm->weightsFoward[m].weight;
								}
							}
						}

						double cell = 0.0;
						double prevCell = 1.0;
						for (int l = 0; l < neuron.size(); l++) {
							if (l == 0 && j == 0) {
								cell = activationFunction((neuron[l]*networkDetails[i]->network->m_layer[j][k]->lstm->weightsRecurrent[0].weight)*(networkDetails[i]->network->m_layer[j][k]->lstm->lstmBiases[0].weight*neuron[l]));
								cell *= networkDetails[i]->network->m_layer[j][k]->lstm->sigmoidFunction((networkDetails[i]->network->m_layer[j][k]->lstm->weightCell[0].weight*prevCell)*(neuron[l]*networkDetails[i]->network->m_layer[j][k]->lstm->weightsRecurrent[1].weight)*(networkDetails[i]->network->m_layer[j][k]->lstm->lstmBiases[1].weight*neuron[l]));
								cell *= networkDetails[i]->network->m_layer[j][k]->lstm->sigmoidFunction((networkDetails[i]->network->m_layer[j][k]->lstm->weightCell[1].weight*prevCell)*(neuron[l]*networkDetails[i]->network->m_layer[j][k]->lstm->weightsRecurrent[2].weight)*(networkDetails[i]->network->m_layer[j][k]->lstm->lstmBiases[2].weight*neuron[l]));
								neuronOne.push_back(activationFunction(cell) * networkDetails[i]->network->m_layer[j][k]->lstm->sigmoidFunction((networkDetails[i]->network->m_layer[j][k]->lstm->weightCell[2].weight*prevCell)*(neuron[l]*networkDetails[i]->network->m_layer[j][k]->lstm->weightsRecurrent[3].weight)*(networkDetails[i]->network->m_layer[j][k]->lstm->lstmBiases[3].weight*neuron[l])));
							} else {
								prevCell = cell;
								cell = activationFunction((neuron[l] * networkDetails[i]->network->m_layer[j][k]->lstm->weightsRecurrent[0].weight)*(networkDetails[i]->network->m_layer[j][k]->lstm->lstmBiases[0].weight*neuron[l]));
								cell *= networkDetails[i]->network->m_layer[j][k]->lstm->sigmoidFunction((networkDetails[i]->network->m_layer[j][k]->lstm->weightCell[0].weight*prevCell)*(neuron[l] * networkDetails[i]->network->m_layer[j][k]->lstm->weightsRecurrent[1].weight)*(networkDetails[i]->network->m_layer[j][k]->lstm->lstmBiases[1].weight*neuron[l]));
								cell *= networkDetails[i]->network->m_layer[j][k]->lstm->sigmoidFunction((networkDetails[i]->network->m_layer[j][k]->lstm->weightCell[1].weight*prevCell)*(neuron[l] * networkDetails[i]->network->m_layer[j][k]->lstm->weightsRecurrent[2].weight)*(networkDetails[i]->network->m_layer[j][k]->lstm->lstmBiases[2].weight*neuron[l]));
								neuronOne[l] += activationFunction(cell) * networkDetails[i]->network->m_layer[j][k]->lstm->sigmoidFunction((networkDetails[i]->network->m_layer[j][k]->lstm->weightCell[2].weight*prevCell)*(neuron[l] * networkDetails[i]->network->m_layer[j][k]->lstm->weightsRecurrent[3].weight)*(networkDetails[i]->network->m_layer[j][k]->lstm->lstmBiases[3].weight*neuron[l]));
							}
						}

						if (k++ == networkDetails[i]->network->m_layer[j].size()) {
							neuron = neuronOne;
							neuronOne.empty();
						}
					}
				}
			}

			vector<double> delta;
			for (int j = 0; j < targets[i].size(); j++) {
				delta.push_back(targets[i][j] - neuron[j]);
			}

			vector<int> accurracy;
			for (int j = 0; j < delta.size(); j++) {
				if (delta[j] <= 0.1) {
					accurracy.push_back(1);
				} else {
					accurracy.push_back(0);
				}
			}

			int halfway = 0;
			if (networkDetails[i]->network->m_layer.size()%2 == 0) {
				halfway = networkDetails[i]->network->m_layer.size()/2;
			} else {
				halfway = (networkDetails[i]->network->m_layer.size()/2)+0.5;
			}

			int count = 0;
			for (int j = 0; j < accurracy.size(); j++) {
				if (accurracy[j] == 1) {
					count += 1;
				}
			}

			if (count >= halfway) {
				change.push_back(1);
			} else {
				change.push_back(0);
			}
		}

		//Find the best weight for the neuron.
		string parentS;
		int parentI;
		int networkCount = 0;
		double updatingWeights;

		for (int i = 0; i < fitnessScore.size(); i++) {
			for (int j = 0; j < fitnessScore[i].size(); j++) {
				parentS = Genomes[i][j][0];
				parentI = fitnessScore[i][j][0];
				for (int k = 0; k < fitnessScore[i][j].size(); k++) {
					if (parentI < fitnessScore[i][j][k]) {
						parentI = fitnessScore[i][j][k];
						parentS = Genomes[i][j][k];
					}
				}

				updatingWeights = (double)parentI;
				updatingWeights = updatingWeights/(updatingWeights+1);
				updatingWeights *= updatingWeights;

				//Update the appropriate networks with the updatingWeights value.
				if (i <= pointOne) {
					if (_audioNetwork->m_layer[i][j]->_ann == true) {
						if (change[i] == 1) {
							for (int k = 0; k < _audioNetwork->m_layer[i][j]->ann->weightsFoward.size(); k++) {
								if (rand() % 2 == 0) {
									_audioNetwork->m_layer[i][j]->ann->weightsFoward[k].weight += updatingWeights;
								} else {
									_audioNetwork->m_layer[i][j]->ann->weightsFoward[k].weight -= updatingWeights;
								}
							}
						}
					} else if (_audioNetwork->m_layer[i][j]->_rnn == true) {
						if (change[i] == 1) {
							for (int k = 0; k < _audioNetwork->m_layer[i][j]->rnn->weightsFoward.size(); k++) {
								if (rand() % 2 == 0) {
									_audioNetwork->m_layer[i][j]->rnn->weightsFoward[k].weight += updatingWeights;
								} else {
									_audioNetwork->m_layer[i][j]->rnn->weightsFoward[k].weight -= updatingWeights;
								}
							}

							for (int k = 0; k < _audioNetwork->m_layer[i][j]->rnn->weightsRecurrent.size(); k++) {
								if (rand() % 2 == 0) {
									_audioNetwork->m_layer[i][j]->rnn->weightsRecurrent[k].weight += updatingWeights;
								} else {
									_audioNetwork->m_layer[i][j]->rnn->weightsRecurrent[k].weight -= updatingWeights;
								}
							}
						}
					}
				} else if (i > pointOne && i <= pointTwo) {
					if (change[i] == 1) {
						for (int k = 0; k < _imageNetwork->m_layer[i][j]->ann->weightsFoward.size(); k++) {
							if (rand() % 2 == 0) {
								_imageNetwork->m_layer[i][j]->ann->weightsFoward[k].weight += updatingWeights;
							} else {
								_imageNetwork->m_layer[i][j]->ann->weightsFoward[k].weight -= updatingWeights;
							}
						}
					}
				} else if (i > pointTwo && i <= pointThree) {
					if (change[i] == 1) {
						if (_textNetwork->m_layer[i][j]->_ann == true) {
							for (int k = 0; k < _textNetwork->m_layer[i][j]->ann->weightsFoward.size(); k++) {
								if (rand() % 2 == 0) {
									_textNetwork->m_layer[i][j]->ann->weightsFoward[k].weight += updatingWeights;
								} else {
									_textNetwork->m_layer[i][j]->ann->weightsFoward[k].weight -= updatingWeights;
								}
							}
						} else if (_textNetwork->m_layer[i][j]->_lstm == true) {
							for (int k = 0; k < _textNetwork->m_layer[i][j]->lstm->weightsFoward.size(); k++) {
								if (rand() % 2 == 0) {
									_textNetwork->m_layer[i][j]->lstm->weightsFoward[k].weight += updatingWeights;
								} else {
									_textNetwork->m_layer[i][j]->lstm->weightsFoward[k].weight -= updatingWeights;
								}
							}

							for (int k = 0; k < _textNetwork->m_layer[i][j]->lstm->weightsRecurrent.size(); k++) {
								if (rand() % 2 == 0) {
									_textNetwork->m_layer[i][j]->lstm->weightsRecurrent[k].weight += updatingWeights;
								} else {
									_textNetwork->m_layer[i][j]->lstm->weightsRecurrent[k].weight -= updatingWeights;
								}
							}

							for (int k = 0; k < _textNetwork->m_layer[i][j]->lstm->weightCell.size(); k++) {
								if (rand() % 2 == 0) {
									_textNetwork->m_layer[i][j]->lstm->weightCell[k].weight += updatingWeights;
								} else {
									_textNetwork->m_layer[i][j]->lstm->weightCell[k].weight -= updatingWeights;
								}
							}
						}
					}
				} else if (i > pointThree && i <= pointFour) {
					if (change[i] == 1) {
						for (int k = 0; k < _videoNetwork->m_layer[i][j]->ann->weightsFoward.size(); k++) {
							if (rand() % 2 == 0) {
								_videoNetwork->m_layer[i][j]->ann->weightsFoward[k].weight += updatingWeights;
							} else {
								_videoNetwork->m_layer[i][j]->ann->weightsFoward[k].weight -= updatingWeights;
							}
						}
					}
				} else {
					if (change[i] == 1) {
						if (networkDetails[networkCount]->network->m_layer[i][j]->_ann == true) {
							for (int k = 0; k < networkDetails[networkCount]->network->m_layer[i][j]->ann->weightsFoward.size(); k++) {
								if (rand() % 2 == 0) {
									networkDetails[networkCount]->network->m_layer[i][j]->ann->weightsFoward[k].weight += updatingWeights;
								} else {
									networkDetails[networkCount]->network->m_layer[i][j]->ann->weightsFoward[k].weight -= updatingWeights;
								}
							}
						} else if (networkDetails[networkCount]->network->m_layer[i][j]->_rnn == true) {
							for (int k = 0; k < networkDetails[networkCount]->network->m_layer[i][j]->rnn->weightsFoward.size(); k++) {
								if (rand() % 2 == 0) {
									networkDetails[networkCount]->network->m_layer[i][j]->rnn->weightsFoward[k].weight += updatingWeights;
								} else {
									networkDetails[networkCount]->network->m_layer[i][j]->rnn->weightsFoward[k].weight -= updatingWeights;
								}
							}

							for (int k = 0; k < networkDetails[networkCount]->network->m_layer[i][j]->rnn->weightsRecurrent.size(); k++) {
								if (rand() % 2 == 0) {
									networkDetails[networkCount]->network->m_layer[i][j]->rnn->weightsRecurrent[k].weight += updatingWeights;
								} else {
									networkDetails[networkCount]->network->m_layer[i][j]->rnn->weightsRecurrent[k].weight -= updatingWeights;
								}
							}
						} else if (networkDetails[networkCount]->network->m_layer[i][j]->_lstm == true) {
							for (int k = 0; k < networkDetails[networkCount]->network->m_layer[i][j]->lstm->weightsFoward.size(); k++) {
								if (rand() % 2 == 0) {
									networkDetails[networkCount]->network->m_layer[i][j]->lstm->weightsFoward[k].weight += updatingWeights;
								} else {
									networkDetails[networkCount]->network->m_layer[i][j]->lstm->weightsFoward[k].weight += updatingWeights;
								}
							}

							for (int k = 0; k < networkDetails[networkCount]->network->m_layer[i][j]->lstm->weightsRecurrent.size(); k++) {
								if (rand() % 2 == 0) {
									networkDetails[networkCount]->network->m_layer[i][j]->lstm->weightsRecurrent[k].weight += updatingWeights;
								} else {
									networkDetails[networkCount]->network->m_layer[i][j]->lstm->weightsRecurrent[k].weight -= updatingWeights;
								}
							}

							for (int k = 0; k < networkDetails[networkCount]->network->m_layer[i][j]->lstm->weightCell.size(); k++) {
								if (rand() % 2 == 0) {
									networkDetails[networkCount]->network->m_layer[i][j]->lstm->weightCell[k].weight += updatingWeights;
								} else {
									networkDetails[networkCount]->network->m_layer[i][j]->lstm->weightCell[k].weight -= updatingWeights;
								}
							}
							networkCount += 1;
						}
					}
				}
			}
		}

		//Update the ID key if the condition to chance it is met.

	}
}

//This method sets up the text based Recurrent Neural Network and the video and image CNN's.
void ArtificialIntelligence::setupAI() {
	vector<vector<string>> audioNetwork;
	vector<vector<string>> imageNetwork;
	vector<vector<string>> textNetwork;
	vector<vector<string>> videoNetwork;
	vector<string> layer;

	//This creates the neural network for Audio.
	audioNetwork.push_back(layer);
	audioNetwork.back().push_back("ANNBlock");

	audioNetwork.push_back(layer);
	audioNetwork.back().push_back("RNNBlock");

	audioNetwork.push_back(layer);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 10; j++) {
			audioNetwork.back().push_back("ANNBlock");
		}
	}

	//This creates the neural network for Image.
	imageNetwork.push_back(layer);
	for (int i = 0; i < 4; i++) {
		imageNetwork.back().push_back("ANNBlock");
	}

	for (int i = 0; i < 2; i++) {
		imageNetwork.push_back(layer);
		for (int j = 0; j < 4; j++) {
			imageNetwork.back().push_back("ANNBlock");
		}
	}

	for (int i = 0; i < 6; i++) {
		imageNetwork.back().push_back("ANNBlock");
	}

	//This creates the neural network for Text.
	textNetwork.push_back(layer);
	for (int i = 0; i < 3; i++) {
		textNetwork.back().push_back("ANNBlock");
	}

	textNetwork.push_back(layer);
	textNetwork.back().push_back("LSTMBlock");

	textNetwork.push_back(layer);
	for (int i = 0; i < 3; i++) {
		textNetwork.back().push_back("ANNBlock");
	}

	//This creates the neural network for Video.
	videoNetwork.push_back(layer);
	for (int i = 0; i < 4; i++) {
		videoNetwork.back().push_back("ANNBlock");
	}

	for (int i = 0; i < 2; i++) {
		videoNetwork.push_back(layer);
		for (int j = 0; j < 4; j++) {
			videoNetwork.back().push_back("ANNBlock");
		}
	}

	for (int i = 0; i < 6; i++) {
		videoNetwork.back().push_back("ANNBlock");
	}

	//This generates the neural networks and stores them in the AI.
	_audioNetwork = new DynamicNetworkGenerator(audioNetwork);
	_imageNetwork = new DynamicNetworkGenerator(imageNetwork);
	_textNetwork = new DynamicNetworkGenerator(textNetwork);
	_videoNetwork = new DynamicNetworkGenerator(videoNetwork);
}

//This creates a new Neural Network for the AI.
void ArtificialIntelligence::addNetwork(int count, vector<vector<string>> networkSetup) {
	threadDetails *td = new threadDetails();
	td->id = bitset<4>(count).to_string();
	td->network = new DynamicNetworkGenerator(networkSetup);
	td->active = true;
	networkDetails.push_back(td);
}

//This calculates the performance of a network from the AI.
string ArtificialIntelligence::networkPerformance() {
	string genome = "";
	for (int i = 0; i < networkDetails.size(); i++) {
		if ((networkDetails[i]->dataSetsProcessed/networkDetails[i]->dataSetsCollected) >= 90.0) {
			genome += "1";
		} else {
			genome += "0";
		}
	}

	return genome;
}