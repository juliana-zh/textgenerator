#include <boost/program_options.hpp>
#include <boost/filesystem/path.hpp>

#include "generator.h"

int main(int argc, char **argv) 
{  
    try 
    {     
        namespace po = boost::program_options; 
        
        Gen::Options opt;
        po::options_description desc("Options"); 
        desc.add_options() 
            ("help"    , "Print help information") 
            ("file,f"  , po::value<boost::filesystem::path>(&opt.fname)->required(), "Input-file for processing")
            ("number,n", po::value<size_t>(&opt.nTokens)->required(), "Minimum number of tokens in result text")
            ;
           
        po::variables_map vm; 
        try 
        { 
            po::store(po::parse_command_line(argc, argv, desc), vm); 
        
            if ( vm.count("help")  ) 
            { 
                std::cout << "Basic Command Line Parameter App" << std::endl 
                        << desc << std::endl; 
                return EXIT_SUCCESS; 
            } 
 
            po::notify(vm); 
                            
        } 
        catch(const po::error& e)
        { 
            std::cerr << "ERROR_IN_COMMAND_LINE: " << e.what() << std::endl << std::endl; 
            std::cerr << desc << std::endl; 
            return EXIT_FAILURE; 
        }
        
        try
        {
             Gen::mainBuilder(opt); 
        }
        catch(const std::exception &e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
            return EXIT_FAILURE;
        }
    } 
    catch (...) 
    { 
        std::cerr << "Unhandled Exception reached the top of main: " 
                << ", application will now exit" << std::endl; 
        return EXIT_FAILURE;     
    } 
 
    return EXIT_SUCCESS;       
}
