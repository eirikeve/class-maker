#include <string>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <exception>
#include <ctime>

using namespace std;


int main(int argc, char** argv) {

    ////////////////////////
    // Edit this!
    string my_name = "My Name";
    ////////////////////////
    
    // ASCII Value of 'a'
    const int LOWERCASE_LO = (int)'a';
    // ASCII Value of 'A'
    const int UPPERCASE_LO = (int)'A';
    // 'a' has higher value than 'A'
    const int DIFF_UPPER_LOWER_CASE = LOWERCASE_LO - UPPERCASE_LO;
    
    string input = "";
    string header = "";
    string source = "";
    string t_text = "";
    
    // Get input
    if ( (argc <= 1) || (argv[argc-1] == NULL) || (argv[argc-1][0] == '-') ) {
        cerr << "Error! No class name specified." << endl;
        return 1;
    }
    if ( argc > 2 )
    {
        cerr << "Error! Multiple inputs." << endl; 
        return 1;
    }
    else {
        input = argv[argc-1];
    }
    for (int i = 0; i < input.size(); ++i)
    {
        if (i == 0 && !isalpha(input[i]))
        {
            cerr << "Error! Class name must start with an alphabetic character." << endl;
            return 1;
        }

        if ( !(isalpha(input[i]) || isdigit(input[i])) )
        {
            cerr << "Error! " << input << " is not a valid class name. Only enter the class name - no file extensions." << endl;
            return 1;
        }
    }

    // Get time
    time_t t = time(0);
    struct tm * now = localtime( & t );
    t_text = to_string(now->tm_mday) + "/" + to_string(now->tm_mon + 1) + "/" + to_string(now->tm_year + 1900);


    // Get text for header filename, source filename, and IFNDEF class identifier
    header = input;
    for (int i = 0; i < header.size(); ++i)
    {
        if (! isdigit(header[i]))
        {
            // To lowercase
            header[i] = (header[i] < LOWERCASE_LO) ? header[i] + DIFF_UPPER_LOWER_CASE : header[i];
        }
    }
    header += ".h";

    source = input;
    for (int i = 0; i < source.size(); ++i)
    {
        if (! isdigit(header[i]))
        {
            // To lowercase
            source[i] = (source[i] < LOWERCASE_LO) ? source[i] + DIFF_UPPER_LOWER_CASE : source[i];
        }
    }
    source += ".cpp";

    string header_ifndef = input;
    for (int i = 0; i < header_ifndef.size(); ++i)
    {
        if (! isdigit(header[i]))
        {
            // To uppercase
            header_ifndef[i] = (header_ifndef[i] < LOWERCASE_LO) ? header_ifndef[i] : header_ifndef[i] - DIFF_UPPER_LOWER_CASE;
        }
    }
    header_ifndef += "_H";

    // Make sure class name starts with an uppercase letter
    input[0] = (input[0] < LOWERCASE_LO) ? input[0] : input[0] - DIFF_UPPER_LOWER_CASE;

    // Get text for class files
    string headertext = "// "+header+"\n// "+ my_name + ", " + t_text+"\n#ifndef "+header_ifndef+"\n#define "+header_ifndef+"\n\n";
    headertext += "class "+input+"\n{\n// Private variables\nprivate:\n\n// Public variables\npublic:\n\n";
    headertext += "// Private methods\nprivate:\n\n// Public methods\npublic:\n\n};\n\n";
    headertext += "#endif //";
    headertext += header_ifndef;
    string sourcetext = "// "+source+"\n// "+ my_name + ", " + t_text+"\n\n#include \""+header+"\"\n";

    // Create file
    try
    {
        // Check that neither file already exists.
        ifstream s(source);
        ifstream h(header);
        if( !h.good() && !s.good() )
        {
            ofstream sourcefile;
            sourcefile.open (source, std::ofstream::out | std::ofstream::trunc);
            sourcefile << sourcetext;
            sourcefile.close();

            ofstream headerfile;
            headerfile.open (header, std::ofstream::out | std::ofstream::trunc);
            headerfile << headertext;
            headerfile.close();

            cout << "Successfully created " << source << " and " << header << "." << endl;

        }
        else
        {
            std::string msg_err = "Error! The following already exists: ";
            if (s.good()) msg_err += (source + " ");
            if (h.good()) msg_err += (header + " ");
            cerr << msg_err << endl;
            return 1;
        }
    } catch (const std::exception &e) {
        cerr << "Error! " << e.what() << endl;
        return 1;
    }
    return 0;
}