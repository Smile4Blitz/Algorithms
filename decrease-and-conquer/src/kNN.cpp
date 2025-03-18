#include "kNN.h"
#include "QuickSelect.h"

std::vector<location> leesData(std::string filename, int number_of_lines)
{
    std::cout << "reading data" << std::endl;
    csv::CSVReader data_in(filename);

    std::vector<location> locations= {};
    int line_count = 0;
    for (auto &row : data_in)
    {
        if(line_count++> number_of_lines){
            break;
        }
        location loc;
        int cnt = 0;
        
        for (auto field: row) {
            if(cnt == 0){
                loc.x = field.get<double>();
            }
            else if(cnt == 1){
                loc.y = field.get<double>();
            }
            else if(field.is_int()){
                loc.RSSi.push_back(field.get<int>());
            }
            else{
                loc.RSSi.push_back(-120);
            }
            cnt++;
        }
        locations.push_back(loc);
    }


    std::cout << "Data reading complete (" << locations.size() << ") lines" << std::endl;
    return locations;
}

/* updates the distances in the traininglist to the new point p1 */
void updateDistance(const location& p1, std::vector<location>& trainingList){
      for(location& l : trainingList) {
        int max = (l.RSSi.size() <= p1.RSSi.size()) ? l.RSSi.size() : p1.RSSi.size();
        l.distance = 0;
        for(int i = 0 ; i < max; i++) {
            l.distance += std::abs(l.RSSi[i] - p1.RSSi[i]);
        }
      }
}

/* calculates the euclidean distance between 2 points for evaluating the final result*/
double euclideanDistance(const location& p1, const location& p2){
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
} 

/* calculates the average location for the k closest points */
location kNN_location(std::vector<location>& list, int k){
    location result = {0,0};
    for(int i = 0; i < k; i++) {
        result.x += list[i].x;
        result.y += list[i].y;
    }
    result.x /= k;
    result.y /= k;
    return result;
}