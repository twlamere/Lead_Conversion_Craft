Intallation
=============

You have multiple options depending on what you're comfortable with. The first
is a console application (i.e. using the command prompt). For this simply copy
the .exe files from that folder to where you want to use them, or you can also
simply copy the source code and recompile. The other option is a desktop
application. In the desktop folder there should be a couple installation .exe
files. Simply download the installation file for your system, run, and you're good to go!

Note: As of 10 August 2015, I've only tested these on Windows computers, so they
might not work on Mac OS X or Linux operating systems.

Usage
=======

Process
---------

Both of the application methods will follow the same general process.

1. Go to LeadConduit and download all desired leads
2. Name them something that makes sense and helps you distinguish, e.g. vendor_date_city.csv
3. Run them through the first conversion program
4. Send them to the e-Bureau FTP server
5. Copy the output XML files from the server
6. Run the output files through the second conversion program
7. Compile the resulting CSV files into an Excel spreadsheet (for tips see section below)

I've included the template excel spreadsheet I use within this repository for you
along with a couple excel macros to make the process more efficient (covered later).

Console Application
-----------------------

For me this is the quicker option as it involves less clicking and just typing
a few letters, tabbing to the correct file, and pressing enter. However, I 
would recommend not using this option if you're unfamiliar with using the 
command prompt.

For this option, I've include two executable programs: ctox.exe and xtoc.exe. ctox.exe 
will be used for converting the downloaded leads to an XML format that can be used
by the e-Bureau server. How to use it is shown below:

```bash
ctox.exe vendor_date_knox.csv vendor_date_ash.csv > vendor_date.xml
```

The filename for Knoxville leads must be entered before the Asheville leads. If there are
no leads for a city, simple type "none" for the file name. Also, the > symbol is very important
as it specifies to output the information to the file specified. Example below:

```bash
ctox.exe none vendor_date_ash.csv > vendor_date.xml
```

Once you've done that for all of the leads for each vender, send them to e-Bureau to score
and copy the output files somewhere. Then use xtoc.exe to convert the output files into 
CSV/Excel files for each vendor.

```bash
xtoc.exe vendor_date.out.xml > vendor_date.out.csv
```

*Tip: only the first few letters of a file name need to be typed. After doing that simply press tab 
and the first file matching the beginning filename will be auto-filled in (press tab again to cycle through).*

Desktop Application
----------------------

Though a little slower (for me), this is the simpler option. After installing the file simply
open up the installed program, and everything else is pretty self explanatory. 

The top half of the user interface is for converting downloaded leads to the 
file format used by e-Bureau to scorethe leads. Simply browse to the files or 
leave blank if a particular city has no leads for that vendor, then browse to 
where you would like to save the resulting file and name it, and then press
convert.

After you send the files to e-Bureau and copy the scored files over to your computer,
use the bottom half of the program to convert it to an Excel/CSV file for each vendor. First browse
to the file and select it, browse to where you would like to save the file and name it, 
and then just press convert once again.

Compiling and Excel Tips
--------------------------