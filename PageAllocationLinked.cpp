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

    int next = -1;

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

    void set_next(int next)
    {
        this->next = next;
    }

    int get_next()
    {
        return next;
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
        if (!(*slot).is_empty() && (*slot).get_file_name() == name)
            return true;

    return false;
}

void set_linked_memory(vector<Block> *memory,
                       vector<int> *index_page,
                       File file)
{
    int index = -1, prev = -1, i = 0;

    if (!file_exists((*memory), file.filename))
    {

        if (get_empty_count(*memory) >= file.size)
        {

            index = generate_index(*memory);

            (*index_page).push_back(index);
            for (i = 0; i < file.size - 1; i++)
            {

                file.partition = i;

                (*memory).at(index).set_file(file);

                prev = index;

                index = generate_index(*memory);

                (*memory).at(prev).set_next(index);
            }

            file.partition = file.size - 1;
            (*memory).at(index).set_file(file);

            cout << "File " << file.filename
                 << " has been successfully allocated"
                 << endl;
        }
        else
            cout << "Not enough available memory"
                 << endl;
    }
    else
        cout << "File already exists in given memory"
             << endl;
}

void delete_from_linked_memory(vector<Block> *memory,
                               vector<int> *index_page,
                               string file)
{
    int index, next, previous, main_index, i = 0;
    vector<int>::iterator slot;

    if (file_exists((*memory), file))
    {

        for (slot = (*index_page).begin();
             slot != (*index_page).end();
             slot++)
        {

            if ((*memory)
                    .at(*slot)
                    .get_file_name() == file)
            {

                main_index = (*slot);

                index = i;
                break;
            }
            i++;
        }

        i = main_index;

        while (i != -1 && (*memory)
                                  .at(i)
                                  .get_file_name() == file)
        {

            (*memory).at(i).set_empty();

            previous = i;

            i = (*memory).at(i).get_next();

            (*memory).at(previous).set_next(-1);
        }

        (*index_page)
            .erase((*index_page)
                       .begin() +
                   index);
        cout << "File " << file
             << " has been successfully deleted"
             << endl;
    }
    else
    {
        cout << "File does not exist in given memory"
             << endl;
    }
}

void show_linked_index(vector<Block> memory,
                       vector<int> index)
{
    int max = 9, i, count;

    vector<int>::iterator slot;

    string fname;

    for (slot = index.begin();
         slot != index.end(); slot++)
    {

        if (memory
                .at(*slot)
                .get_file_name()
                .length() > max)
        {
            max = memory
                      .at(*slot)
                      .get_file_name()
                      .length();
            cout << "+" << string(max + 2, '-')
                 << "+---------------+---------"
                 << "----+------------------+";
            cout << "\n|"
                 << string(max / 2 + max % 2 - 4,
                           ' ')
                 << "File Name"
                 << string(max / 2 - 3, ' ');
            cout << "| Start Address | End Address"
                 << " | Size of the file |\n+"
                 << string(max + 2, '-');
            cout << "+---------------+--------"
                 << "-----+------------------+"
                 << endl;
        }
    }

    for (slot = index.begin();
         slot != index.end();
         slot++)
    {

        i = (*slot);
        fname = memory
                    .at(i)
                    .get_file_name();
        count = 1;
        while (memory.at(i).get_next() != -1 && memory
                                                        .at(i)
                                                        .get_file_name() == fname)
        {
            i = memory.at(i).get_next();
            count++;
        }

        cout << "|" << string(max / 2 + max % 2 - memory.at(*slot).get_file_name().length() / 2 - memory.at(*slot).get_file_name().length() % 2 + 1, ' ')
             << memory
                    .at(*slot)
                    .get_file_name()
             << string(max / 2 - memory.at(*slot).get_file_name().length() / 2 + 1,
                       ' ')
             << "|"
             << string(8 - to_string(*slot).length() / 2 - to_string(*slot).length() % 2,
                       ' ')
             << (*slot)
             << string(7 - to_string(*slot)
                                   .length() /
                               2,
                       ' ')
             << "|"
             << string(7 - to_string(i).length() / 2 - to_string(i).length() % 2,
                       ' ')
             << i
             << string(6 - to_string(i)
                                   .length() /
                               2,
                       ' ')
             << "|"
             << string(9 - to_string(count).length() / 2 - to_string(count).length() % 2,
                       ' ')
             << count
             << string(9 - to_string(count)
                                   .length() /
                               2,
                       ' ')
             << "|" << endl;
    }

    cout << "+" << string(max + 2, '-')
         << "+---------------+----------"
         << "---+------------------+"
         << endl;
}

void show_linked_indexes(vector<Block> memory, vector<int> index_page,
                         string filename)
{
    int index;
    vector<int>::iterator slot;

    if (file_exists(memory, filename))
    {
        cout << "File Name = " << filename;
        cout << "\n+------------------+----------"
             << "--------+------------------+";
        cout << "\n| Current Location |Next part"
             << " Location| Partition Number |";
        cout << "\n+------------------+----------"
             << "--------+------------------+\n";

        for (slot = index_page.begin();
             slot != index_page.end(); slot++)
        {
            if (memory
                    .at(*slot)
                    .get_file_name() == filename)
            {
                index = (*slot);
                break;
            }
        }

        while (index != -1)
        {
            cout << "|"
                 << string(9 - to_string(index).length() / 2 - to_string(index).length() % 2,
                           ' ')
                 << index
                 << string(9 - to_string(index)
                                       .length() /
                                   2,
                           ' ')
                 << "|"
                 << string(9 - to_string(memory.at(index).get_next()).length() / 2 - to_string(memory.at(index).get_next()).length() % 2,
                           ' ')
                 << memory
                        .at(index)
                        .get_next()
                 << string(9 - to_string(memory
                                             .at(index)
                                             .get_next())
                                       .length() /
                                   2,
                           ' ')
                 << "|"
                 << string(9 - to_string(memory.at(index).get_file_partition_no()).length() / 2 - to_string(memory.at(index).get_file_partition_no()).length() % 2,
                           ' ')
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
            index = memory
                        .at(index)
                        .get_next();
        }

        cout << "+------------------+---------"
             << "---------+------------------+"
             << endl;
    }
    else
    {
        cout << "Given file does not exist"
             << " in given memory"
             << endl;
    }
}

int main()
{

    vector<Block> memory(16);

    vector<int> index_page;
    File temp;
    cout << "Remaining memory :- "
         << get_empty_count(memory) << endl;

    temp.filename = "home.txt";
    temp.size = 5;
    set_linked_memory(&memory,
                      &index_page,
                      temp);

    temp.filename = "Report.docx";
    temp.size = 6;
    set_linked_memory(&memory,
                      &index_page,
                      temp);

    temp.filename = "new_img.png";
    temp.size = 3;
    set_linked_memory(&memory,
                      &index_page,
                      temp);

    temp.filename = "test.cpp";
    temp.size = 2;
    set_linked_memory(&memory,
                      &index_page, temp);

    cout << "Files have been successfully set"
         << endl;
    cout << "Remaining memory :- "
         << get_empty_count(memory) << endl;

    show_linked_index(memory, index_page);
    cout << "Now we will check index"
         << " of each partition of ";
    cout << "Report.docx and test.cpp"
         << " before deleting them"
         << endl;

    show_linked_indexes(memory, index_page,
                        "Report.docx");

    show_linked_indexes(memory, index_page,
                        "test.cpp");

    delete_from_linked_memory(&memory,
                              &index_page,
                              "Report.docx");
    delete_from_linked_memory(&memory,
                              &index_page,
                              "test.cpp");
    cout << "Remaining memory :- "
         << get_empty_count(memory) << endl;

    show_linked_index(memory, index_page);

    temp.filename = "hello.jpeg";
    temp.size = 8;

    set_linked_memory(&memory,
                      &index_page,
                      temp);
    cout << "Check index page :- "
         << endl;

    show_linked_index(memory, index_page);

    cout << "Remaining memory :- "
         << get_empty_count(memory) << endl;
    cout << "We will check each partition for"
         << " hello.jpeg ";
    cout << "to see if deleted locations are"
         << " utilized or not"
         << endl;

    show_linked_indexes(memory,
                        index_page,
                        "hello.jpeg");
    memory.clear();
    memory.shrink_to_fit();
    index_page.clear();
    index_page.shrink_to_fit();

    return 0;
}
