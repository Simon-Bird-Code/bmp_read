LOGSTDOUT = True

class __bmp_cpp:
        Running = False;

        def calc_bmp_row_padding ( self , pixel_width , pixel_colours ):
            # bmp has padding to fill out each row, it is in segments of 4, thus need to fill with trailing zeros
            # needs to be 4=0 3=1 2=2 1=3 0=0  if remainder == 0 returns 4;
            ret = 0;
            rgb_pieces = pixel_width * pixel_colours;
            spacer = rgb_pieces % 4; # find remainder
            if(LOGSTDOUT):
                print ( 'spacer' + str(spacer) )
            if(spacer==0):
                return 0
            ret = 4 - spacer

            return ret;

        def pixel_hook ( self , pixel_data_in ):
            ret=1
            return 1
    
        def read_bmp( self , file_name_in ,hook ):
            ret=-1;
            
            iFile = open ( file_name_in , "rb" )
            # to return
            
            file_header = []
           
            header_size=54;  #/// standard header
            bmp_pixels=3;    #/// depth of colour
            padding_byte=0;  #/// to be set

            #ifstream iFile;     iFile.open( file_name_in.c_str() ,ios::binary );

            ch='';

            if(LOGSTDOUT):
                print( "File Open" )

            #-- read header
            i=0
            while(i<(header_size)):
                i+=1
                ch=iFile.read(1)
                file_header.append(ch)
                if(LOGSTDOUT):
                   print(ch)

            if(LOGSTDOUT):
                print("conversion")
            # convert size from header binary [pos] to int
            bmp_width = 0
            bmp_width += ( int.from_bytes(file_header[18], byteorder='big') )
            bmp_width += ( ( int.from_bytes(file_header[19], byteorder='big') ) << 8 )
            bmp_width += ( ( int.from_bytes(file_header[20], byteorder='big') ) << 16 )
            bmp_width += ( ( ( int.from_bytes(file_header[21], byteorder='big') ) << 24 ) * 256 )

            bmp_height = 0
            bmp_height += ( int.from_bytes(file_header[22], byteorder='big') )
            bmp_height += ( ( int.from_bytes(file_header[23], byteorder='big') ) << 8 )
            bmp_height += ( ( int.from_bytes(file_header[24], byteorder='big') ) << 16 )
            bmp_height += ( ( ( int.from_bytes(file_header[25], byteorder='big') ) << 24 ) * 256 )
            if(LOGSTDOUT):
                print(bmp_height)
                print(bmp_width)
            count=0
            local_vector_height = []
            local_vector_width = []
            for width in range (bmp_width):
                for height in range (bmp_height):
                    pixel_data = []
                    pixel_data.append(iFile.read(1))
                    pixel_data.append(iFile.read(1))
                    pixel_data.append(iFile.read(1))
                    count+=1
                    if(LOGSTDOUT):
                        print (width)
                        print (height)
                    self.pixel_hook(pixel_data)
                    local_vector_width.append(pixel_data)
                local_vector_height.append(local_vector_width)
            if(LOGSTDOUT):
                print ( count )
            
            return local_vector_height;

bmp_c = __bmp_cpp()

bmp_c.read_bmp("tfile.bmp",True)

print('done')
