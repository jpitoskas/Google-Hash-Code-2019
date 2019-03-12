#pragma GCC optimize("Ofast")

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <set>

using namespace std;

class Photo
{
  public:
    int id;
    bool orientation; // HORIZONTAL 0, VERTICAL 1
    vector<string> tags;
    bool isAvailable;

    Photo(){};
    Photo(int id, bool orientation, const vector<string> &tags) : id(id), orientation(orientation), isAvailable(true)
    {
        for (unsigned int i = 0; i < tags.size(); i++)
        {
            this->tags.push_back(tags[i]);
        }
    };
    ~Photo(){};

    friend ostream &operator<<(ostream &os, const Photo &photo)
    {
        os << "PHOTO " << photo.id << '\n';
        os << "ORIENTATION: " << photo.orientation << '\n';
        os << "TAGS: ";
        for (unsigned int i = 0; i < photo.tags.size(); i++)
        {
            os << photo.tags[i] << " ";
        }
        os << "\n\n";
        return os;
    }
};

class Slide
{
  public:
    std::vector<int> id;
    bool orientation;
    set<string> tags;
    bool isAvailable;

    Slide();
    Slide( Photo& p) : orientation(p.orientation) , isAvailable(true)
    {
        id.push_back(p.id);
        tags.insert(p.tags.begin(), p.tags.end());
    };

    Slide(Photo& p1,  Photo& p2) : orientation(p1.orientation), isAvailable(true)
    {
        id.push_back(p1.id);
        id.push_back(p2.id);
        p1.tags.insert(p1.tags.end(), p2.tags.begin(), p2.tags.end());
        tags.insert(p1.tags.begin(), p1.tags.end());
    }
    ~Slide(){};

    friend ostream &operator<<(ostream &os, const Slide &slide)
    {
        os << "SLIDE " << '\n';
        os << "ID: ";
        for(int i = 0; i < slide.id.size(); i++) 
        {
            os << slide.id[i] << " ";
        }
        os << '\n';
        os << "ORIENTATION: " << slide.orientation << '\n';
        os << "TAGS: ";
        for (auto i = slide.tags.begin(); i != slide.tags.end(); i++)
        {
            os << *i << " ";
        }
        os << "\n\n";
        return os;
    }
};

// auto compare = [](const Photo& r1, const Photo& r2) -> bool {
//     if (r1.m_speed != r2.m_speed)
//         return r1.m_speed < r2.m_speed;
//     return r1.x0() <= r2.x0();
// };

void deletePhoto(std::vector<Photo>& photos, const Photo& toBeErased)
{
	for (unsigned int i = 0; i < photos.size(); i++)
	{
		if (toBeErased.id == photos[i].id)
			photos.erase(photos.begin() + i);
	}
}

pair<vector<Photo>, vector<Photo>>
readFile(unsigned int fileIndex, string *inputFilePaths, int size, int &N, char &orientation, int &num_tags, vector<string> &tags)
{
    ifstream file(inputFilePaths[fileIndex]);

    string line;
    stringstream buffer;

    while (getline(file, line))
    {
        buffer << line << '\n';
    }

    // cout << buffer.str() << endl;
    buffer >> N;

    vector<Photo> photos, horizontal_photos, vertical_photos;
    // photos.reserve(N);
    // horizontal_photos.reserve(N);
    // vertical_photos.reserve(N);
    for (int i = 0; i < N; i++)
    {
        buffer >> orientation >> num_tags;
        tags.resize(num_tags);
        for (int j = 0; j < num_tags; j++)
        {
            buffer >> tags[j];
        }

        photos.emplace_back(i, (orientation == 'H') ? true : false, tags);
        if (orientation == 'H')
        {
            horizontal_photos.push_back(photos[i]);
        }
        else
        {
            vertical_photos.push_back(photos[i]);
        }
    }

    return {horizontal_photos, vertical_photos};
}

void writeFile(unsigned int fileIndex, string *outputFilePaths, int size, const vector<Slide> &slides)
{
    ofstream output;
    output.open(outputFilePaths[fileIndex]);

    output << slides.size() << "\n";
    for (auto& it : slides)
    {
        for(int i = 0; i < it.id.size(); i++)
        {
            output << it.id[i] << " ";

        }
        output << '\n';
    }

    output.close();
}

int find_common_tags(const vector<string>& tags1, const vector<string>& tags2)
{
    int common_tags = 0;
    for (unsigned int i = 0; i < tags1.size(); i++)
    {
        for (unsigned int j = 0; j < tags2.size(); j++)
        {
            if(tags1[i] == tags2[j])
            {
                common_tags++;
            }
        }
    }
    return common_tags;
}

int find_common_tags(const set<string>& tags1, const set<string>& tags2)
{
    int common_tags = 0;
    for (auto& it : tags1)
    {
        for (auto& it2 : tags2)
        {
            if(it == it2)
            {
                common_tags++;
            }
        }
    }
    return common_tags;
}

int find_score(const Slide& s1, const Slide& s2)
{
    int common_tags = find_common_tags(s1.tags, s2.tags);
    int v1 = s1.tags.size() - common_tags;
    int v2 = s2.tags.size() - common_tags;
    int first_min =  min(v1, v2);
    return (first_min, common_tags);
}

const int NUM_FILES = 5;

int main(int argc, char** argv)
{

    unsigned int fileIndex = atoi(argv[1]);
    string inputFilePaths[NUM_FILES] = {"Files/a.in", "Files/b.in", "Files/c.in", "Files/d.in", "Files/e.in"};

    int N, num_tags;
    vector<string> tags;
    char orientation;

    pair<vector<Photo>, vector<Photo>> photos;
    photos = readFile(fileIndex, inputFilePaths, NUM_FILES, N, orientation, num_tags, tags);

    // for(int i = 0; i < photos.first.size(); i++)
    // {photos.first[i]
    // }
    // for(int i = 0; i < photos.second.size(); i++)
    // {
    // }
    // cerr << photos.first.size() << '\n';
    // cerr << photos.second.size();

    // Slide
    vector<Slide> slides;
    // slides.reserve(N);
    for (unsigned int i = 0; i < photos.first.size(); i++)
    {
        slides.emplace_back(photos.first[i]);
    }

    // for (unsigned int i = 0; i < photos.second.size() - 1; i++)
    // {
    //     if(photos.second[i].isAvailable)
    //     {
    //         int max = 0;
    //         int max_id = -1;
    //         for (unsigned int j = i + 1; j < photos.second.size(); j++)
    //         {
    //             if(photos.second[j].isAvailable)
    //             {
    //                 int common = find_common_tags(photos.second[i].tags, photos.second[j].tags);
    //                 if(common >= max)
    //                 {
    //                     max = common;
    //                     max_id = j;

    //                 }  
    //             }          
    //         }
    //         slides.emplace_back(photos.second[i], photos.second[max_id]);
    //         photos.second[i].isAvailable = false;
    //         photos.second[max_id].isAvailable = false;
    //     }
    // }

    if(photos.second.size() != 0)
    {
        for (int i = 0; i < (int)(photos.second.size() - 2); i += 2)
        {
            // cout << photos.second[i];
            slides.emplace_back(photos.second[i], photos.second[i + 1]);
        }
    }

    vector<Slide> final_slides;
    // final_slides.reserve(slides.size());
    for(int i = 0; i < slides.size(); i++)
    {
        if(slides[i].isAvailable)
        {
            int max_score = -1000;
            int max_id = -1;
            for(int j = i + 1; j < slides.size(); j++)
            {
                if(slides[j].isAvailable)
                {
                    int score = find_score(slides[i], slides[j]);
                    if(score > max_score)
                    {
                        max_score = score;
                        max_id = j;
                    }
                }
            }

            if(max_id != -1)
            {
                final_slides.push_back(slides[i]);
                slides[i].isAvailable = false;
                final_slides.push_back(slides[max_id]);
                slides[max_id].isAvailable = false;
            }
        }
        
    }

    // Output
    string outputFilePaths[5] = { "Files/output_a.out" ,"Files/output_b.out" ,"Files/output_c.out" ,"Files/output_d.out", "Files/output_e.out" };
    writeFile(fileIndex, outputFilePaths, NUM_FILES, final_slides);

    return 0;
}