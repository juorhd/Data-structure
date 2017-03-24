#include <vector>
#include <iomanip>
#include <list>
#include <cmath>	

#include "image.h"
#include "visualization.h"
using namespace std;

class Seed{
public:
	Seed (int xx, int yy, float sd, float average) : x(xx), y(yy), stand_div(sd), avg(average) {}
	int x,y;
	float stand_div; 	//standard diviation for the pixel differnece in seed
	float avg;
};

// ======================================================================
// Helper function to read the optional arguments and filenames from
// the command line.
void parse_arguments(int argc, char* argv[], 
                     std::string& method, int& seed, int& table_size, float& compare,
                     std::vector<std::string>& filenames) {
  for (int i = 1; i < argc; i++) {
    if (argv[i] == std::string("-method")) {
      i++;
      assert (i < argc);
      method = argv[i];
      assert (method == "simple" || method == "hashtable");
    } else if (argv[i] == std::string("-seed")) {
      i++;
      assert (i < argc);
      seed = atoi(argv[i]);
      assert (seed >= 1);
    } else if (argv[i] == std::string("-table")) {
      i++;
      assert (i < argc);
      table_size = atoi(argv[i]);
      assert (table_size >= 1);
    } else if (argv[i] == std::string("-compare")) {
      i++;
      assert (i < argc);
      compare = atof(argv[i]);
      assert (compare > 0.0 && compare <= 1.0);
    } else {
      filenames.push_back(argv[i]);
    }
  }
  assert (filenames.size() > 0);
}


// ======================================================================
// This simple algorithm is rather inefficient, and may not find the
// largest overlapping subregion.  But it will find a subregion match
// of size seed x seed, if one exists.
void SimpleCompare(const Image<int>& a, const Image<int>& b, 
                   Image<Color> &out, int which_color,int seed, float& percent,
                   std::vector<std::pair<BoundingBox,BoundingBox> >& regions) {

  // First, find a small seed that matches
  bool found = false;
  Point offset_a;
  Point offset_b;

  // Search over all possible points in image a
  for (int i = 0; i <= a.Width()-seed && !found; i++) {
    for (int j = 0; j <= a.Height()-seed && !found; j++) {
      // Search over all possible points in image b
      for (int i2 = 0; i2 <= b.Width()-seed && !found; i2++) {
        for (int j2 = 0; j2 <= b.Height()-seed && !found; j2++) {
          bool match = true;
          // Check for small seed match
          for (int x = 0; x < seed && match; x++) {
            for (int y = 0; y < seed && match; y++) {
              if (a.GetPixel(i+x,j+y) != b.GetPixel(i2+x,j2+y)) {
                match = false;
              }
            }
          }
          if (match) {
            // break out of these loops!
            HighlightSeed(out,which_color,Point(i,j),seed);
            found = true;
            offset_a = Point(i,j);
            offset_b = Point(i2,j2);
          }
        }
      }
    }
  }
  if (!found) {
    // no match between these images
    percent = 0.0;
    return;
  } 

  int width = seed;
  int height = seed;
  int max_x = 0;
  int max_y = 0;

  // First, expand the region match widthwise, until we hit the right
  // edge of one of the images or a mismatched pixel.
  for (width = seed; width + offset_a.x < a.Width() && width + offset_b.x < b.Width(); width++)
    for (int h_for_current_width = 0; h_for_current_width + offset_a.y < a.Height() 
    									&& h_for_current_width + offset_b.y < b.Height(); h_for_current_width++)
      if (a.GetPixel(width + offset_a.x, h_for_current_width + offset_a.y) 
      		!= b.GetPixel(width + offset_b.x, h_for_current_width + offset_b.y))
        break;

  // Then, expand the region match heightwise, until we hit the top
  // edge of one of the images or a mismatched pixel.
  for (height = seed; height + offset_a.y < a.Height() && height + offset_b.y < b.Height(); height++)
    for (int w_for_current_height = 0; w_for_current_height + offset_a.x < a.Width() 
    		&& w_for_current_height + offset_b.x < b.Width(); w_for_current_height++)
      if (a.GetPixel(w_for_current_height + offset_a.x, height + offset_a.y) 
      		!= b.GetPixel(w_for_current_height + offset_b.x, height + offset_b.y))
        break;


  BoundingBox bbox_a(offset_a,Point(offset_a.x+width-1,offset_a.y+height-1));
  BoundingBox bbox_b(offset_b,Point(offset_b.x+width-1,offset_b.y+height-1));
  regions.push_back(std::make_pair(bbox_a,bbox_b));
  // return fraction of pixels
  percent = bbox_a.Width()*bbox_a.Height() / float (a.Width()*a.Height());
}

// ======================================================================
int hashfunction(float stand_div, float avg, int total, int table_size ) {
	int num = floor((sqrt(stand_div)+sqrt(avg))*sqrt(total)*144.14159); 
		return num % table_size; 
}

void HashCompare(const Image<int>& a, const Image<int>& b, Image<Color> &out,
                   int table_size, int which_color,int seed, float& percent,
                   float compare, std::vector<std::pair<BoundingBox,BoundingBox> >& regions){

	vector<list<Seed> > Hashtable_A(table_size);        //create memory to store seeds
	vector<list<Seed> > Hashtable_B(table_size);

	for ( int i=0; i< a.Width()-seed; ++i){             //loop to put seeds in hashtables
		for ( int j=0; j< a.Height()-seed; ++j){
			int total = 0;
			int avg;
			float stand_div = 0;
			for ( int w=0; w<seed; ++w){
				for (int h=0; h<seed; ++h){
					int color = a.GetPixel(i+w, j+h);
					total += color;						//calculate the total grayscale for the seed
				}
			}
			avg = total*1.0/seed/seed;
			for ( int w=0; w<seed; ++w){
				for (int h=0; h<seed; ++h){
					int color = a.GetPixel(i+w, j+h);
					stand_div += (avg-color)*(avg-color); //calculate the standard diviation for the seed
				}
			}
			int index = hashfunction(stand_div, avg, total, table_size);
			Hashtable_A[index].push_back(Seed(i, j, stand_div, avg));
		}
	}
	for ( int i=0; i< b.Width()-seed; ++i){
		for ( int j=0; j< b.Height()-seed; ++j){
			int total = 0;
			int avg;
			float stand_div = 0;
			for ( int w=0; w<seed; ++w){
				for (int h=0; h<seed; ++h){
					int color = b.GetPixel(i+w, j+h);
					total += color;
				}
			}
			avg = total*1.0/seed/seed;
			for ( int w=0; w<seed; ++w){
				for (int h=0; h<seed; ++h){
					int color = b.GetPixel(i+w, j+h);
					stand_div += (avg-color)*(avg-color);
				}
			}
			int index = hashfunction(stand_div, avg, total, table_size);
			Hashtable_B[index].push_back(Seed(i, j, stand_div, avg));	
	 	}
	}

	vector<Seed> hashA;
	vector<Seed> hashB;

	for (int i=0; i<table_size*compare; ++i){
		if ( Hashtable_A[i].size() && Hashtable_B[i].size() ){						//go through fraction of hashtables to compare the similarities
			list<Seed>::iterator itrA;
			list<Seed>::iterator itrB;
			for (itrA=Hashtable_A[i].begin(); itrA!=Hashtable_A[i].end(); ++itrA)
				for (itrB=Hashtable_B[i].begin(); itrB!=Hashtable_B[i].end(); ++itrB){
					if ( (*itrA).avg!=(*itrB).avg || (*itrA).stand_div!=(*itrB).stand_div) //pass if average or standard diviation doesnt match
						continue;
					for (int w=0; w<seed; ++w)
						for (int h=0; h<seed; ++h)
							if (a.GetPixel((*itrA).x+w,(*itrA).y+h)==b.GetPixel((*itrB).x+w,(*itrB).y+h)){ //add the seed to the vector for further modification
								hashA.push_back(*itrA);
								hashB.push_back(*itrB);
								HighlightSeed(out, which_color, Point(itrA->x, itrA->y), seed);
							}		
				}
		}
	}

	if ( hashA.size() && hashB.size() ){ 				//find the leftbottom and righttop point function
		int maxAx, maxAy, maxBx, maxBy;
		int minAx, minAy, minBx, minBy;
	   	maxAx = minAx = hashA[0].x;
	   	maxBx = minBx = hashB[0].x;
	   	maxAy = minAy = hashA[0].y;
	   	maxBy = minBy = hashB[0].y; 
		for (int i=0; i<hashA.size(); ++i){
			maxAx = max(maxAx, hashA[i].x);
			maxAy = max(maxAy, hashA[i].y);
			minAx = min(minAx, hashA[i].x);
			minAy = min(minAy, hashA[i].y);
		}
		for (int i=0; i<hashB.size(); ++i){
			maxBx = max(maxBx, hashB[i].x);
			maxBy = max(maxBy, hashB[i].y);
			minBx = min(minBx, hashB[i].x);
			minBy = min(minBy, hashB[i].y);
		}
		BoundingBox bbox_a(Point(minAx, minAy), Point(maxAx+seed-1, maxAy+seed-1));  //draw the box
		BoundingBox bbox_b(Point(minBx, minBy), Point(maxBx+seed-1, maxBy+seed-1));
		regions.push_back(make_pair(bbox_a,bbox_b));
		percent = bbox_a.Width()*bbox_a.Height() / float (a.Width()*a.Height());
	} else percent = 0;
}

int main(int argc, char* argv[]) {

  // default command line argument values
  std::string method = "simple";
  int seed = 5;
  int table_size = 1000000;
  float compare = 0.05;
  std::vector<std::string> filenames;
  parse_arguments(argc,argv,method,seed,table_size,compare,filenames);


  // Load all of the images
  std::vector<Image<int> > images(filenames.size());
  for (int i = 0; i < filenames.size(); i++) {
    images[i].Load(filenames[i]);
  }

  // Loop over all input images, comparing to every other input image
  for (int a = 0; a < filenames.size(); a++) {
    std::cout << filenames[a] << std::endl;
    // prepare a color visualization image for each input file
    Image<Color> out;
    InitializeOutputFile(images[a],out);
    int which_color = -1;
    for (int b = 0; b < filenames.size(); b++) {
      if (a == b) continue;
      which_color++;
      
      // Find the one (or more!) subregions that match between this pair of images
      std::vector<std::pair<BoundingBox,BoundingBox> > regions;
      float percent = 0.0;
      if (method == "simple") {
        SimpleCompare(images[a],images[b],out,which_color,seed,percent,regions);
      } else {
        assert (method == "hashtable");
        HashCompare(images[a],images[b],out,table_size,which_color,seed,percent,compare,regions);
      } 

      std::cout << std::right << std::setw(7) << std::fixed << std::setprecision(1) 
                << 100.0 * percent << "% match with " << std::left << std::setw(20) << filenames[b];

      for (int i = 0; i < regions.size(); i++) {
        std::cout << "   " << regions[i].first << " similar to " << regions[i].second;
        // add the frame data to the visualization image
        DrawBoundingBox(out,regions[i].first,which_color);
      }
      std::cout << std::endl;
      // Save the visualization image
      std::string f = "output_" + filenames[a].substr(0,filenames[a].size()-4) + ".ppm";
      out.Save(f);
    }
  }
}
