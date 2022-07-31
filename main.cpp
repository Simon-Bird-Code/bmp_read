#include <iostream>
#include <vector>
#include <fstream>
#define LOGSTDOUT true
using namespace std;

struct _bmp_pixel_data
{
    int r=0;
    int g=0;
    int b=0;
};

struct _bmp_size
{
    int height=0;
    int width=0;
};

struct _bmp_struct_bmp
{
    _bmp_size bmp_size;
    vector <int> file_header;
    vector <_bmp_pixel_data> bmp_pixel_data;
};



class __bmp_cpp
{
private:
    bool Running = false;

    /// used to get set right segment
    int header_lookup ( string header_id){int ret=0;return ret;}
public:
    void bmp_cpp() { Running = true; }

    long get_header_info ( int header_segment_id )
    {
        long ret=0;
        return ret;
        /// lookup here, and reverse true
    }

    long set_header_info ( int header_segment_id , long header_data )
    {
        long ret=0;
        return ret;
        /// lookup here, and reverse true
    }

    int calc_bmp_row_padding ( int pixel_width ,  int pixel_colours );

    _bmp_struct_bmp read_bmp( string file_name_in , bool hook );

    void read_bmp_hook(_bmp_pixel_data local_pixel,int h,int w);
};


void __bmp_cpp::read_bmp_hook(_bmp_pixel_data local_pixel,int h,int w)
    {
        cout << h << " - " << w << endl;
        cout << local_pixel.r << " - " << local_pixel.g << " - " << local_pixel.b << endl;
    }

/// bmp has padding to fill out each row, it is in segments of 4, thus need to fill with trailing zeros
int __bmp_cpp::calc_bmp_row_padding ( int pixel_width ,  int pixel_colours )
{
    /// needs to be 4=0 3=1 2=2 1=3 0=0  if remainder == 0 returns 4;
    int ret = 0;
    int rgb_pieces = pixel_width * pixel_colours;
    int spacer = rgb_pieces % 4; /// find remainder

    if(spacer==0){return 0;}
    ret = 4 - spacer;

    return ret;
}

/// only works if the pallet is standard, ie standard header length, need to make in a new edit, to handle longer files,
/// ie header with its own pallet

_bmp_struct_bmp __bmp_cpp::read_bmp ( string file_name_in , bool hook = false )
{
    /// to return
    _bmp_struct_bmp local_vector;

    int header_size=54;  /// standard header
    int bmp_pixels=3;    /// depth of colour
    int padding_byte=0;  /// to be set

    ifstream iFile;     iFile.open( file_name_in.c_str() ,ios::binary );

    char ch;

    if(iFile.is_open())
        {
            if(LOGSTDOUT){cout << " File Open"<<endl;}

/// -- read header
            for( int i=0; i<header_size; i++ )   {    iFile.get(ch);   local_vector.file_header.push_back((unsigned char)ch); }


/// -- decode sizes
            int bmp_width = local_vector.file_header.at(18) + (  local_vector.file_header.at(19) << 8 )
                + (  local_vector.file_header.at(20) << 16 ) + ( 256 * local_vector.file_header.at(21) << 24 );

            int bmp_height = local_vector.file_header.at(22) + (  local_vector.file_header.at(23) << 8 )
                + (  local_vector.file_header.at(24) << 16 ) + ( 256 * local_vector.file_header.at(25) << 24 );

            local_vector.bmp_size.height=bmp_height;
            local_vector.bmp_size.width=bmp_width;

/// -- log out
            if(LOGSTDOUT){cout << "h=" << bmp_height << ":w=" << bmp_width << endl;}

/// -- get pixel data
            for( int h=0; h<bmp_height;  h++ )
                {   for(int w=0;w<bmp_width;w++)
                        {
							_bmp_pixel_data local_pixel;

								iFile.get(ch);   local_pixel.b=(unsigned char)ch;
								iFile.get(ch);   local_pixel.g=(unsigned char)ch;
								iFile.get(ch);   local_pixel.r=(unsigned char)ch;

                            local_vector.bmp_pixel_data.push_back(local_pixel);

                            if(hook){ read_bmp_hook(local_pixel,h,w); }
                        }

                    int row_end_padding=calc_bmp_row_padding( bmp_width , bmp_pixels );

                    for(int we=0;we<row_end_padding;we++)
                        {
                                iFile.get(ch);   padding_byte=ch; if(padding_byte==0){}
                        }
                }

/// -- tidy up + error
        iFile.close();
		return local_vector;
        }
    else cout << "Unable to open file"<<endl;
    return local_vector;
}




int main()
{
    __bmp_cpp bmpread;
    bmpread.read_bmp("tfile.bmp",true);
    cout << "Hello world!" << endl;
    return 0;
}

