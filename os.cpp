//
//  main.cpp
//  os_hw1
//
//  Created by Fiona on 15/2/9.
//  Copyright (c) 2015年 Fiona. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int pass;
int line = 0, offset = 1;
int error_No = -1;
char x;
bool first_char = true;
int last_line = 0, last_offset = 0;
int num_instr = 0;
int memory_count = 0;

map<string, bool> is_defined;
map<string, int> define_times;
map<string, int> symbol_addr;


class definition{
public:
    string name;
    int address;
    int module_id;
    
    definition(string n, int addr, int m){
        name = n;
        address = addr;
        module_id = m;
    }
};

class item{
public:
    string type;
    int address;
    
    item(string t, int addr){
        type = t;
        address = addr;
    }
};

void __parseerror(int errcode, int line, int offset) {
    string errstr[7] = {
        
        "NUM_EXPECTED",             // Number expect
        "SYM_EXPECTED",             // Symbol Expected
        "ADDR_EXPECTED",            // Addressing Expected
        "SYM_TOLONG",               // Symbol Name is to long
        "TO_MANY_DEF_IN_MODULE",    // > 16
        "TO_MANY_USE_IN_MODULE",    //>16
        "TO_MANY_INSTR",            // total num_instr exceeds memory size (512)
    };
    
    cout<<"Parse Error line "<<line<<" offset "<<offset<<": "<<errstr[errcode]<<endl;
    
    //printf("Parse Error line %d offset %d: %s\n", linenum, lineoffset, errstr[errcode]); }
}

//void position_update(int &offset, int &line, char x){
void position_update(){
    
    if(first_char){
        line++;
        offset = 1;
    }
    
    if(x == ' '){
        if(!first_char)
            offset++;
        
        first_char = false;
        
        //cout<<line<<"-"<<offset<<": ";
        //cout<<"space "<<x;
    }
    else if(x == '\t'){
        if(!first_char)
            offset++;
        
        first_char = false;
        
        //cout<<line<<"-"<<offset<<": ";
        //cout<<"\\t "<<x;
    }
    else if(x == '\n'){
        if(!first_char)
            offset++;
        
        //cout<<line<<"-"<<offset<<": ";
        //cout<<"\\n "<<x;
        
        
        first_char = true;
    }
    else{
        if(!first_char)
            offset++;
        
        first_char = false;
        
        //cout<<line<<"-"<<offset<<": ";
        //cout<<x<<" ";
    }
    
}

string get_symbol(ifstream &the_file){
    string ans;
    
    if(x != ' ' && x != '\t' && x != '\n'){
        ans.push_back(x);
        
        if( !((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')) ) {
            error_No = 1;
            
            return "#";
        }
        
        while(the_file.get(x) && x != ' ' && x != '\t' && x != '\n'){
            position_update();
            /*
             if( !((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')) ) {
             error_No = 1;
             
             return "#";
             }*/
            
            ans.push_back(x);
        }
        
    }else{
        
        while(the_file.get(x)){
            position_update();
            
            if(x != ' ' && x != '\t' && x != '\n')
                break;
        }
        
        if( !((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')) ) {
            error_No = 1;
            
            return "#";
        }
        
        ans.push_back(x);
        
        while(the_file.get(x) && x != ' ' && x != '\t' && x != '\n'){
            position_update();
            /*
             if( !((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')) ) {
             error_No = 1;
             
             return "#";
             }*/
            
            ans.push_back(x);
        }
    }
    
    position_update();
    
    
    return ans;
}

int get_number(ifstream &the_file){
    int ans = 0;
    
    if(x != ' ' && x != '\t' && x != '\n'){
        ans = int(x) - '0';
        
        if(int(x) - '0' < 0 || int(x) - '0' > 9){
            error_No = 0;
            return -1;
        }
        
        while(the_file.get(x) && x != ' ' && x != '\t' && x != '\n'){
            position_update();
            ans = ans * 10 + int(x) - '0';
            if(int(x) - '0' < 0 || int(x) - '0' > 9){
                error_No = 0;
                return -1;
            }
        }
    }else{
        
        while(the_file.get(x)){
            position_update();
            
            if(x != ' ' && x != '\t' && x != '\n')
                break;
        }
        
        ans = int(x) - '0';
        
        if(int(x) - '0' < 0 || int(x) - '0' > 9){
            error_No = 0;
            return -1;
        }
        
        while(the_file.get(x) && x != ' ' && x != '\t' && x != '\n'){
            position_update();
            ans = ans * 10 + int(x) - '0';
            
            if(int(x) - '0' < 0 || int(x) - '0' > 9){
                error_No = 0;
                return -1;
            }
        }
    }
    
    position_update();
    
    return ans;
}

vector<definition> read_def(ifstream &the_file, int id){
    vector<definition> result;
    string name;
    int addr = 0;
    
    last_line = line;
    last_offset = offset;
    
    int def_count = get_number(the_file);
    
    if(def_count == -1){
        return result;
    }else if(def_count > 16){
        line = last_line;
        offset = last_offset;
        
        error_No = 4;
        return result;
    }
    
    for(int i = 0; i < def_count; i++){
        
        name = get_symbol(the_file);
        
        if(name == "#"){
            return result;
        }else if(name.length() > 16){
            
            error_No = 3;
            
            return result;
        }
        
        addr = get_number(the_file);
        
        if(addr == -1){
            return result;
        }
        
        
        
        
        
        if(is_defined[name]  != true){
            
            
            result.push_back(definition(name, addr, id));
            
            is_defined[name]  = true;
            define_times[name] = 1;
        }else{
            define_times[name]++;
        }
        
        
    }
    
    return result;
}

vector<string> read_use(ifstream &the_file){
    vector<string> result;
    string name;
    
    last_line = line;
    last_offset = offset;
    
    if(first_char){
        last_line ++;
        last_offset = 1;
    }
    
    int use_count = get_number(the_file);
    
    if(use_count == -1){
        return result;
    }else if(use_count > 16){
        line = last_line;
        offset = last_offset;
        error_No = 5;
        
        return result;
    }
    
    for(int i = 0; i < use_count; i++){
        
        name = get_symbol(the_file);
        
        if(name == "#"){
            return result;
        }else if(name.length() > 16){
            
            error_No = 3;
            
            return result;
        }
        
        result.push_back(name);
    }
    
    return result;
}

vector<item> read_prog(ifstream &the_file){
    
    vector<item> result;
    string type;
    int addr;
    
    last_line = line;
    last_offset = offset;
    
    if(first_char){
        last_line ++;
        last_offset = 1;
    }
    
    int prog_count = get_number(the_file);
    
    num_instr += prog_count;
    
    if(prog_count == -1){
        line = last_line;
        offset = last_offset;
        
        return result;
    }else if(num_instr > 512){
        error_No = 6;
        line = last_line;
        offset = last_offset;
        
        return result;
    }
    
    for(int i = 0; i < prog_count; i++){
        type = get_symbol(the_file);
        
        if(type == "#"){
            error_No = 2;
            return result;
        }
        
        addr = get_number(the_file);
        
        if(addr == -1){
            return result;
        }
        
        result.push_back(item(type, addr));
    }
    
    return result;
}

int read_module(ifstream &the_file, int module_id, vector<definition> &total_def_list, int base){
    
    vector<definition> def_list = read_def(the_file, module_id);
    
    
    if(error_No != -1){
        return 0;
    }
    
    
    
    vector<string> use_list = read_use(the_file);
    
    if(error_No != -1){
        return 0;
    }
    
    vector<item> pro_list = read_prog(the_file);
    
    if(error_No != -1){
        return 0;
    }
    
    int max = base + pro_list.size() - 1;
    
    for(int i = 0; i < def_list.size(); i++){
        if(def_list[i].address > max){
            cout<<"Warning: Module "<<module_id + 1<<": "<<def_list[i].name<<" to big "<<def_list[i].address<<" (max="<<max<<") assume zero relative"<<endl;
            def_list[i].address = 0;
            total_def_list.push_back(def_list[i]);
        }else{
            total_def_list.push_back(def_list[i]);
        }
    }
    
    return pro_list.size();
}

void print_4_digits_num(int num){
    if(num < 10){
        cout<<"000"<<num;
    }else if(num < 100){
        cout<<"00"<<num;
    }else if(num < 1000)
        cout<<"0"<<num;
    else{
        cout<<num;
    }
}

void print_memory(int num){
    if(memory_count < 10){
        cout<<"00"<<memory_count<<": ";
        print_4_digits_num(num);
        memory_count++;
        
    }else if(memory_count < 100){
        cout<<"0"<<memory_count<<": ";
        print_4_digits_num(num);
        memory_count++;
        
    }else{
        cout<<memory_count<<": ";
        print_4_digits_num(num);
        memory_count++;
    }
}

int read_memory_map(ifstream &the_file, int module_id, map<string, bool> &appear_is_used, map<string, bool> &defined_is_used, vector<int> module_base){
    
    vector<definition> stream1 = read_def(the_file, module_id);
    
    
    vector<string> use_list = read_use(the_file);
    vector<item> pro_list = read_prog(the_file);
    
    for(int i = 0; i < pro_list.size(); i++){
        //cout<<pro_list[i].type<<" "<<pro_list[i].address<<"  ";
        
        if(pro_list[i].type == "E"){
            
            int k = pro_list[i].address % 1000;
            int opcode = pro_list[i].address - k;
            
            if(pro_list[i].address > 9999){
                print_memory(9999);
                cout<<" Error: Illegal opcode; treated as 9999";
            }else if(k > use_list.size() - 1){
                print_memory(pro_list[i].address);
                cout<<" Error: External address exceeds length of uselist; treated as immediate";
            }else{
                string symbol = use_list[k];
                //int s_addr = symbol_addr[symbol];
                
                if( is_defined[symbol] == true ){
                    
                    appear_is_used[symbol] = true;
                    defined_is_used[symbol] = true;
                    
                    int plus_addr = opcode + symbol_addr[symbol];
                    print_memory(plus_addr);
                }else{
                    print_memory(opcode);
                    appear_is_used[symbol] = true;
                    defined_is_used[symbol] = true;
                    
                    cout<<" Error: "<<symbol<<" is not defined; zero used";
                }
                
            }
        }else if(pro_list[i].type == "A"){
            
            int k = pro_list[i].address % 1000;
            int opcode = pro_list[i].address - k;
            
            if(pro_list[i].address > 9999){
                print_memory(9999);
                cout<<" Error: Illegal opcode; treated as 9999";
            }else if(k > 512){
                print_memory(opcode);
                cout<<" Error: Absolute address exceeds machine size; zero used";
            }else{
                print_memory(pro_list[i].address);
            }
            
            
        }else if(pro_list[i].type == "I"){
            
            if(pro_list[i].address > 9999){
                print_memory(9999);
                cout<<" Error: Illegal immediate value; treated as 9999";
            }
            else
                print_memory(pro_list[i].address);
            
        }else if(pro_list[i].type == "R"){
            
            if(pro_list[i].address > 9999){
                print_memory(9999);
                cout<<" Error: Illegal opcode; treated as 9999";
            }else{
                //cout<<"*** "<<module_id<<" "<<module_base[module_id]<<endl;
                
                int k = pro_list[i].address % 1000;
                int opcode = pro_list[i].address - k;
                
                if(k > (module_base[module_id + 1] - module_base[module_id])){
                    
                    print_memory(opcode + module_base[module_id]);
                    
                    cout<<" Error: Relative address exceeds module size; zero used";
                }else
                    print_memory(pro_list[i].address + module_base[module_id]);
            }
            
            
        }
        
        
        cout<<endl;
        
    }
    
    
    for(int i = 0; i < use_list.size(); i++){
        
        if(appear_is_used[use_list[i]] == 0){
            cout<<"Warning: Module "<<module_id + 1<<": "<<use_list[i]<<" appeared in the uselist but was not actually used"<<endl;
        }
        
    }
    
    
    
    return pro_list.size();
}

vector<definition> pass_one(ifstream &the_file, vector<int> &module_base){
    
    vector<definition> symbol_table;
    int module_id = 0, size;
    int base = 0;
    
    pass = 1;
    module_base.push_back(0);
    
    
    while ( the_file.get (x) ){
        position_update();
        
        size = read_module(the_file, module_id, symbol_table, base);
        
        if(error_No != -1){
            return symbol_table;
        }
        
        size = module_base[module_base.size()-1] + size;
        base = size;
        module_base.push_back(size);
        module_id++;
    }
    
    cout<<"Symbol Table"<<endl;
    
    for(int i = 0; i < symbol_table.size(); i++){
        symbol_table[i].address += module_base[symbol_table[i].module_id];
        cout<<symbol_table[i].name<<"="<<symbol_table[i].address;
        
        symbol_addr[symbol_table[i].name] = symbol_table[i].address;
        
        if(define_times[symbol_table[i].name] > 1)
            cout<<" Error: This variable is multiple times defined; first value used";
        
        cout<<endl;
    }
    
    
    
    return symbol_table;
}

void pass_two(ifstream &the_file, vector<definition> &symbol_table, vector<int> module_base){
    int module_id = 0, size;
    map<string, bool> defined_is_used;
    
    pass = 2;
    
    cout<<"Memory Map"<<endl;
    
    while ( the_file.get (x) ){
        position_update();
        
        map<string, bool> appear_is_used;
        
        size = read_memory_map(the_file, module_id, appear_is_used, defined_is_used, module_base);
        module_id++;
    }
    
    cout<<endl;
    
    for(int i = 0; i < symbol_table.size(); i++){
        
        if(defined_is_used[symbol_table[i].name] == 0)
            cout<<"Warning: Module "<<symbol_table[i].module_id + 1<<": "<<symbol_table[i].name<<" was defined but never used"<<endl;
    }
    
}

int main ( int argc, char *argv[] )
{
    if ( argc != 2 ) // argc should be 2 for correct execution
        // We print argv[0] assuming it is the program name
        cout<<"usage: "<< argv[0] <<" <filename>\n";
    else {
        // We assume argv[1] is a filename to open
        ifstream the_file (argv[1]);
        // Always check to see if file opening succeeded
        
        
        
        if (!the_file.is_open())
            cout<<"Could not open file\n";
        else{
            
            vector<definition> symbol_table;
            vector<int> module_base;
            
            symbol_table = pass_one(the_file, module_base);
            
            if(error_No != -1){
                __parseerror(error_No, line, offset);
                
                return 0;
            }
            
            the_file.close();
            
            ifstream the_file (argv[1]);
            
            cout<<endl;
            
            pass_two(the_file, symbol_table, module_base);
            
            the_file.close();
            
            
        }
        
        
    }
}


