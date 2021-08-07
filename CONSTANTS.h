#pragma once
const int NUM_SIMS = 100000;
const double MARGIN_OF_ERROR = 3.0;
const int AVERAGE_SAMPLE_SIZE = 1008;
const double mean = 0;
const double std_dev = sqrt(MARGIN_OF_ERROR);
const double min_allowed = -3*std_dev;
const double max_allowed = 3*std_dev;