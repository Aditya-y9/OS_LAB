

#include <iostream>
#include <vector>
using namespace std;

class File
{
public:
    string filename;

    size_t size;

    int partition;
};

class Block
{

    bool occupied = false;

    File file;

public:
    void set_file(File file)
    {
        this->file = file;
        occupied = true;
    }

    string get_file_name()
    {
        return file.filename;
    }

    int get_file_partition_no()
    {
        return file.partition;
    }

    bool is_empty()
    {
        return !occupied;
    }

    void set_empty()
    {
        occupied = false;
    }
};

int get_empty_count(vector<Block> memory)
{
    int sum = 0;
    vector<Block>::iterator slot;

    for (slot = memory.begin();
         slot != memory.end(); slot++)
        sum += (*slot).is_empty();
    return sum;
}

int generate_index(vector<Block> memory)
{
    int index = -1;

    if (!get_empty_count(memory) == 0)
    {

        do
        {
            index = rand() % memory.size();
            index = abs(index);

        } while (!memory.at(index).is_empty());
    }
    return index;
}

bool file_exists(vector<Block> memory,
                 string name)
{
    vector<Block>::iterator slot;

    for (slot = memory.begin();
         slot != memory.end(); slot++)
    {
        if (!(*slot).is_empty() && (*slot).get_file_name() == name)
        {
            return true;
        }
    }

    return false;
}

void set_indexed_memory(vector<Block> *memory,
                        vector<vector<int>> *index_page,
                        File file)
{
    int index;

    vector<int> newpage;

    if (file_exists((*memory), file.filename))
        cout << "File already exists" << endl;
    else
    {

        if (get_empty_count(*memory) >= file.size)
        {

            for (int i = 0; i < file.size; i++)
            {

                index = generate_index(*memory);

                file.partition = i;

                (*memory).at(index).set_file(file);

                newpage.push_back(index);
            }

            (*index_page).push_back(newpage);
            cout << "File " << file.filename
                 << " has been successfully allocated"
                 << endl;
        }
        else
        {
            cout << "Not enough available space"
                 << endl;
        }
    }
}

void delete_from_indexed_memory(vector<Block> *memory,
                                vector<vector<int>> *index_page,
                                string file)
{
    vector<int>::iterator slot;
    vector<vector<int>>::iterator it;
    int index, i = 0;

    if (file_exists((*memory), file))
    {

        for (it = (*index_page).begin();
             it != (*index_page).end(); it++)
        {

            slot = (*it).begin();

            if ((*memory)
                    .at(*slot)
                    .get_file_name() == file)
            {

                index = i;
                break;
            }
            i++;
        }

        for (slot = (*index_page).at(index).begin();
             slot != (*index_page).at(index).end();
             slot++)
            (*memory).at(*slot).set_empty();

        (*index_page)
            .erase((*index_page).begin() + index);
        cout << "File " << file
             << " has been successfully deleted"
             << endl;
    }
    else
    {
        cout << "File does not exist"
             << endl;
    }
}

void show_indexed_index(vector<Block> memory,
                        vector<vector<int>> index_page)
{
    int max = 9;
    vector<Block>::iterator slot;
    vector<vector<int>>::iterator it;

    for (it = index_page.begin();
         it != index_page.end(); it++)
    {
        if (memory
                .at((*it)
                        .at(0))
                .get_file_name()
                .length() > max)
        {
            max = memory
                      .at((*it)
                              .at(0))
                      .get_file_name()
                      .length();
            cout << "+" << string(max + 2, '-')
                 << "+---------------+----------"
                 << "---+------------------+\n|"
                 << string(max / 2 + max % 2 - 4, ' ')
                 << "File Name"
                 << string(max / 2 - 3, ' ')
                 << "| Start Address | End Address"
                 << " | Size of the file |\n+"
                 << string(max + 2, '-')
                 << "+---------------+------"
                 << "-------+------------------+"
                 << endl;
        }
    }

    for (it = index_page.begin();
         it != index_page.end(); it++)
    {
        cout << "|"
             << string(max / 2 + max % 2 - memory.at((*it).at(0)).get_file_name().length() / 2 - memory.at((*it).at(0)).get_file_name().length() % 2 + 1,
                       ' ')
             << memory
                    .at((*it)
                            .at(0))
                    .get_file_name()
             << string(max / 2 - memory.at((*it).at(0)).get_file_name().length() / 2 + 1,
                       ' ')
             << "|"
             << string(8 - to_string((*it).at(0)).length() / 2 - to_string((*it).at(0)).length() % 2,
                       ' ')
             << ((*it).at(0))
             << string(7 - to_string((*it)
                                         .at(0))
                                   .length() /
                               2,
                       ' ')
             << "|"
             << string(7 - to_string((*it).at((*it).size() - 1)).length() / 2 - to_string((*it).at((*it).size() - 1)).length() % 2,
                       ' ')
             << (*it)
                    .at((*it).size() - 1)
             << string(6 - to_string((*it)
                                         .at((*it)
                                                 .size() -
                                             1))
                                   .length() /
                               2,
                       ' ')
             << "|"
             << string(9 - to_string((*it).size()).length() / 2 - to_string((*it).size()).length() % 2,
                       ' ')
             << (*it).size()
             << string(9 - to_string((*it)
                                         .size())
                                   .length() /
                               2,
                       ' ')
             << "|" << endl;
        cout << "+" << string(max + 2, '-')
             << "+---------------+----------"
             << "---+------------------+"
             << endl;
    }
}

void show_indexed_indexes(vector<Block> memory,
                          vector<vector<int>> index_page,
                          string filename)
{
    int index, i = 0, main_index;
    vector<vector<int>>::iterator slot;

    if (file_exists(memory, filename))
    {
        for (slot = index_page.begin();
             slot != index_page.end(); slot++)
        {
            if (memory.at((*slot).at(0)).get_file_name() == filename)
            {
                main_index = i;
                break;
            }
            i++;
        }

        cout << "File Name = " << filename << endl;
        cout << "File page index at main index :- "
             << main_index
             << "\n+------------------+------------------+\n";
        cout << "| Current Location | Partition Number |\n";
        cout << "+------------------+------------------+\n";
        for (i = 0;
             i < index_page.at(main_index).size();
             i++)
        {
            index = index_page
                        .at(main_index)
                        .at(i);
            cout << "|" << string(9 - to_string(index).length() / 2 - to_string(index).length() % 2, ' ')
                 << index
                 << string(9 - to_string(index)
                                       .length() /
                                   2,
                           ' ')
                 << "|" << string(9 - to_string(memory.at(index).get_file_partition_no()).length() / 2 - to_string(memory.at(index).get_file_partition_no()).length() % 2, ' ')
                 << memory
                        .at(index)
                        .get_file_partition_no()
                 << string(9 - to_string(memory
                                             .at(index)
                                             .get_file_partition_no())
                                       .length() /
                                   2,
                           ' ')
                 << "|" << endl;
        }

        cout << "+------------------+----"
             << "--------------+" << endl;
    }
    else
    {
        cout << "File does not exist"
             << endl;
    }
}

int main()
{

    vector<Block> memory(16);

    vector<vector<int>> index_page;

    File temp;
    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;

    temp.filename = "home.txt";
    temp.size = 5;
    set_indexed_memory(&memory,
                       &index_page,
                       temp);

    temp.filename = "Report.docx";
    temp.size = 6;
    set_indexed_memory(&memory,
                       &index_page,
                       temp);

    temp.filename = "new_img.png";
    temp.size = 3;
    set_indexed_memory(&memory,
                       &index_page,
                       temp);

    temp.filename = "test.cpp";
    temp.size = 2;
    set_indexed_memory(&memory,
                       &index_page,
                       temp);

    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;

    show_indexed_index(memory, index_page);
    cout << "Now we will check each partition"
         << " for Report.docx and test.cpp"
         << " before deleting them" << endl;

    show_indexed_indexes(memory, index_page,
                         "Report.docx");

    show_indexed_indexes(memory, index_page,
                         "test.cpp");

    delete_from_indexed_memory(&memory,
                               &index_page,
                               "Report.docx");

    delete_from_indexed_memory(&memory,
                               &index_page,
                               "test.cpp");

    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;

    show_indexed_index(memory, index_page);

    temp.filename = "hello.jpeg";
    temp.size = 8;

    set_indexed_memory(&memory,
                       &index_page,
                       temp);
    cout << "Check index page :- "
         << endl;

    show_indexed_index(memory, index_page);

    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;
    cout << "We will check each partition"
         << " for hello.jpeg to see ";
    cout << "if the locations of deleted files"
         << " are utilized or not" << endl;

    show_indexed_indexes(memory, index_page,
                         "hello.jpeg");
    memory.clear();
    memory.shrink_to_fit();
    index_page.clear();
    index_page.shrink_to_fit();
    return 0;
}
