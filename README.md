Installation
=============

You have multiple options depending on what you're comfortable with. The first
is a console application (i.e. using the command prompt). For this simply copy
the .exe files from that folder to where you want to use them, or you can also
simply copy the source code and recompile. The other option is a desktop
application. There a couple download links to these installation files below.
Simply download the installation file for your system, run, and you're good to go!

- [Mac Install](https://app.box.com/leadconverisoncraft-mac "Install Lead Conversion for Mac OS X"): Go to "More" and then click "Download." You may have to extract a zip file afterward; otherwise, it should be immediately runnable.
- [Windows Install](https://github.com/twlamere/Lead_Conversion_Craft/raw/master/desktop_app/LeadConversionInstaller.exe "Install Lead Converstion for Windows")



How to Use the Applications
=============================

### Process

Both of the application methods will follow the same general process.

1. Go to LeadConduit and download all desired leads
2. Name them something that makes sense and helps you distinguish, e.g. vendor_date_city.csv
3. Run them through the first conversion program
4. Send them to the e-Bureau FTP server
5. Copy the output XML files from the server
6. Run the output files through the second conversion program
7. Compile the resulting CSV files into an Excel spreadsheet (for tips see section below)

I've included the [template excel spreadsheet](https://github.com/twlamere/Lead_Conversion_Craft/raw/master/South%20College%20Data%20file%20Month%20dd.xlsx "Excel Template") I use within this repository for you
along with a couple excel macros to make the process more efficient (covered later).

### Console Application

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
as it specifies to output the information to the file specified. Example for singular file below:

```bash
ctox.exe none vendor_date_ash.csv > vendor_date.xml
```

Once you've done that for all of the leads for each vender, send them to e-Bureau to score 
and, then copy the output files somewhere on your computer. Then use xtoc.exe to convert the output files into 
CSV/Excel files for each vendor.

```bash
xtoc.exe vendor_date.out.xml > vendor_date.out.csv
```

*Tip: only the first few letters of a file name need to be typed. After doing that simply press tab 
and the first file matching the beginning filename will be auto-filled in (press tab again to cycle through).*

### Desktop Application

Though a little slower (for me), this is the simpler option. After installing the program simply
open up the installed program, and everything else is pretty self explanatory. 

The top half of the user interface is for converting downloaded leads to the 
file format used by e-Bureau to score the leads. Simply browse to the files or 
leave blank if a particular city has no leads for that vendor, then browse to 
where you would like to save the resulting file and name it, and then press
convert.

After you send the files to e-Bureau and copy the scored files over to your computer,
use the bottom half of the program to convert it to an Excel/CSV file for each vendor. First browse
to the file and select it, browse to where you would like to save the file and name it, 
and then just press convert once again.


Compiling and Excel Tips
===========================

After following the entire process, converting leads and scoring them, you should
now have a final CSV file for each vendor. Open all of those along with the [template
spreadsheet](https://github.com/twlamere/Lead_Conversion_Craft/raw/master/South%20College%20Data%20file%20Month%20dd.xlsx "Excel Template") (make sure to have a blank template stored somewhere so 
that you can reuse and copy it in the future). You'll now follow a process to compile
them into the report:

1. Copy each vendor CSV file into the respective tab in the template
2. Compile the tabs into the tab for all leads
3. Sort all leads by zip to split up into Knoxville and Asheville
4. Sort all tabs by score
5. Rename "All Leads" tab to desired date and Save as... "South College Data file [Date]"
6. You're all done! Although, I would double-check that the numbers of leads are correct, etc.

Now depending on how you go about this process, it can take you anywhere from 5-10 
minutes and up to an hour. Thus I will now give some tips on how to make this
process as efficient as possible.

### Copying Each Vendor File

*Note: the tips in this section will be most helpful to Windows users. Though they can
be used on other operating systems, I am not sure of their keyboard shortcuts.*

Right now you should have all your excel files open. Most people know that Ctrl+c 
(+ just means to press keys in order simultaneously) is to copy something and 
Ctrl+v is to paste. Here are a couple more and how to use them:

- **Ctrl+c**: this copies highlighted text or cells.
- **Ctrl+v**: this pastes copied text or cells into the highlighted section.
- **Ctrl+Shift+[Arrow key]**: this will highlight all cells in the respective direction
within Excel. Use this for maximum advantage by clicking in the top-left cell of content
desired, press Ctrl+Shift+→ and Ctrl+Shift+↓ (or simply Ctrl+Shift+→+↓) to select all cells
with content to the right and below, and then press Ctrl+c to copy all the cells highlighted.
- **Alt+Tab**: this will switch what window is open. So, after copying cells in one Excel window
use this to switch to the template window to paste them. And then use this to switch back
to the CSV file to close it or to another CSV file.
- **Ctrl+Tab**: this will switch what tab is open. After the template window is open, you can
use this to switch which tab you're in so that you can paste the copied data from the CSV file.
- **Alt+F4**: this will close the open window. I use this to close a CSV file after I copy its
content.

One more note for this section, when you paste the cells from the CSV to the template,
the color scheme will be overwritten. To undo this but keep the values, press Ctrl and then v
after pasting. So what you'll do is press Ctrl+v to paste, press Ctrl to open up paste options, 
and then press v to select paste-by-value.

### Combining Tabs

At this point all the data should be in your Excel file for the report. Use the macro below 
to compile the content from all tabs into the All Leads tab. **The macro will not work** if 
the first tab is not All Leads, second and third tabs are by city, and the rest are leads 
by vendor. This is the main reason why I've provided my template spreadsheet.

```vba
Option Explicit
Sub Combine()
    Dim J As Integer
    On Error Resume Next
    
    Application.ScreenUpdating = False
    
    Sheets(4).Activate
    Range("A1").EntireRow.Select
    Selection.Copy Destination:=Sheets(1).Range("A1")
    
    For J = 4 To Sheets.Count
    
        Sheets(J).Activate
        If Cells(2, 2) <> "" Then
        
            Range("A1").Select
            Selection.CurrentRegion.Select
            Selection.Offset(1, 0).Resize(Selection.Rows.Count - 1).Select
            Selection.Copy Destination:=Sheets(1).Range("A65536").End(xlUp)(2)
        End If
    Next
    
    Application.ScreenUpdating = True
    Sheets(1).Activate
End Sub
```

### Sort All Tabs by Score

After everything is in the spreadsheet and after you've split up All Leads by zipcode
and put them in their respective tabs, you'll have a bunch of unsorted data in all your
tabs. To sort them by score you could go into each tab one by one, but that would take
a while. Instead use the macro below. This macro will only work if you used the same
headers as my template file has (another major reason I provided my template spreadsheet).

```vba
Sub Sort_All()
    Dim ws As Worksheet
    
    Application.ScreenUpdating = False
    
    For Each ws In ActiveWorkbook.Worksheets
        ws.Activate
        Columns("B:B").Select
        ActiveWorkbook.ActiveSheet.Sort.SortFields.Clear
        ActiveWorkbook.ActiveSheet.Sort.SortFields.Add Key:=Range _
            ("B1"), SortOn:=xlSortOnValues, Order:=xlDescending, DataOption:= _
            xlSortNormal
        With ActiveWorkbook.ActiveSheet.Sort
        .SetRange Range("A2:I1048576")
        .Header = xlNo
        .MatchCase = False
        .Orientation = xlTopToBottom
        .SortMethod = xlPinYin
        .Apply
        End With
        Cells(1, 1).Select
    Next
    
    Application.ScreenUpdating = True
    Sheets(1).Activate
End Sub
```

### Using Macros and Saving Them for Future Use

First make sure you have the Developer option in Excel (it'll be at the tope where File,
Home, Insert, etc. are). If you don't, go to File->Options->"Customize Ribbon" and then 
check Developer and press OK. You could copy and paste the macros above into new macros
you create each time and then run them, but that would not be ideal. Instead we want
to copy and paste them once and be able to use them everytime in the future without hassle.
To do this, is a little complicated. [Check out this page that describes how.](https://support.office.com/en-ca/article/Copy-your-macros-to-a-Personal-Macro-Workbook-aa439b90-f836-4381-97f0-6e4c3f5ee566 "Save Macros for Future Use")