Intallation
=============

You have multiple options depending on what you're comfortable with. The first
is a console application (i.e. using the command prompt). For this simply copy
the .exe files from that folder to where you want to use them, or you can also
simply copy the source code and recompile. The other option is a desktop
application. In the desktop folder there should be a couple installation .exe
files. Simply download that, run, and you're good to go!


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
7. Compile the resulting CSV files into an Excel spreadsheet

I've included the template excel spreadsheet I use within this repository for you
along with a couple excel macros to make the process  more efficient (covered later).

Console application
-----------------------

For me this is the quicker option as it involves less clicking and just typing
a few letters, tabbing to the correct file, and pressing enter. However, I 
would recommend not using this option, if you're unfamiliar with using the 
command prompt.

For this option, I've include two executable programs: ctox.exe and xtoc.exe. ctox.exe 
will be used for converting the downloaded leads to an XML format that can be used
by the e-Bureau server. How to use it is shown below:

```bash
ctox.exe vendor_date_knox.exe vendor_date_ash.exe > vendor_date.xml
```

It is required to enter the Knoxville leads file before the Asheville leads. If there are
no leads for a city, simple type "none" for the file name. Also, the > symbol is very important
as it specifies to output the information to the file specified. Example below:

```bash
ctox.exe none vendor_date_ash.exe > vendor_date.xml
```

