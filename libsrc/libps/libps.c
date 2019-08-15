/*---------------------------------------------------------------------------*\
|                                                                             |
| File:        libps.c                                                        |
| Purose:      Is a library of postscript level 2 plot functions              |
|                                                                             |
| Function:    void Hplots(FILE *plot_file,int condition)                     |
| Purpose:     initialize .ps file.                                           |
|                                                                             |
| Function:    void Newpage(FILE *plot_file,int *label, int *ordinal)         |
| Purpose:     handle new pagination                                          |
|                                                                             |
| Function:    void Endpage(FILE *plot_file)                                  |
| Purpose:     handle ending of each page                                     |
|                                                                             |
| Function:    void Plot(FILE *plot_file,float x, float y,int num)            |
| Purpose:     plot line to point x,y                                         |
|                                                                             |
| Function:    void PlotCircle(FILE *plot_file,float Xor, float yor,          |
|                              float radius, int pts,                         |
|                              float red,float green,float blue,              |
|                              int fill)                                      |
| Purpose:     plot circle                                                    |
|                                                                             |
| Function:    void PlotCross(FILE *plot_file,double xpt, double ypt,         |
|                             double linewidth,double size,                   |
|                             double red, double green, double blue)          |
| Purpose:     plot cross                                                     |
|                                                                             |
| Function:    void PlotTriangle(FILE *plot_file,double xpt, double ypt,      |
|                                double linewidth,double size,                |
|                                double red, double green, double blue,       |
|                                int fill)                                    |
| Purpose:     plot triangle                                                  |
|                                                                             |
| Function:    void PlotArrow(FILE *plot_file,float xpt,float ypt,            |
|                             double angle,double size,double red,            |
|                             double green, double blue)                      |
| Purpose:      plot arrow                                                    |
|                                                                             |
| Function:     void ConvertRGBtoHSV(double *H,double *S,double *V,           |
|                                    double *R,double *G,double *B)           |
| Purpose;      convert RGB triple to HSV values                              |
|                                                                             |
| Function:     void ConvertHSVtoRGB(double *h,double *s,double *v,           |
|                                    double *r,double *g,double *b)           |
| Purpose:      convert HSV triple to RGB                                     |
|                                                                             |
| Function:     void HplotsBbox(FILE *plot_file,int condition,                |
|                               int llx,int lly,int urx,int ury)              |
| Purpose:      including bounding box information in initialization of plot  |
|               file.                                                         |
|                                                                             |
| Function:     void PlotNumber(FILE *plot_file,double height,double angle,   |
|               double xpt,double ypt,double number,char *font,double red,    |
|               double green, double blue,int ndec)                           |
| Purpose:      plot a number                                                 |
|                                                                             |
| Function:     void PlotString(FILE *plot_file,double height,double angle,   |
|               double xpt,double ypt,char *string,char *font,double red,     |
|               double green, double blue,int nchar)                          |
| Purpose:      plot a string                                                 |               
|                                                                             |               
|-----------------------------------------------------------------------------|
| David Brown, CTBTO/IDC: Feb 2011                                            |
|                                                                             |
\*---------------------------------------------------------------------------*/

#include "config.h"
#include "libps.h"

/********************************************************************/
/*                                                                  */
/*     CheckLib: returns 1 for library testing                      */
/*                                                                  */
/*                                                                  */
int CheckLib_ps()
{
   return EXIT_SUCCESS;
}

/********************************************************************/
/*                                                                  */
/*     Hplots:  -initialize/terminate plot file                     */
/*       condition:  1 start  0 end                                 */
/*                                                                  */
/*                                                                  */
void Hplots(FILE *plot_file,int condition)
{
  if (condition == 1)
  {
    fprintf(plot_file,"%\%!PS-Adobe-3.0\n");
    fprintf(plot_file,"%\%\%\%EndComments \n");
    fprintf(plot_file,"%\%\%\%BeginProlog \n");
    fprintf(plot_file,"%\%\%\%EndProlog \n");
    fprintf(plot_file,"%\%\%\%BeginSetup \n");
    fprintf(plot_file,"/pM  {stroke newpath moveto} def\n");
    fprintf(plot_file,"/pL  {lineto} def\n");
    fprintf(plot_file,"/hVB {/Helvetica-Bold findfont \n");
    fprintf(plot_file,"     exch scalefont setfont} def\n") ;
    fprintf(plot_file,"/hV  {/Helvetica findfont \n");
    fprintf(plot_file,"     exch scalefont setfont} def\n");
    fprintf(plot_file,"/cO  {/Courier findfont \n");
    fprintf(plot_file,"     exch scalefont setfont} def\n");
    fprintf(plot_file,"/fA {/Symbol findfont   \n");
    fprintf(plot_file,"      exch scalefont setfont} def\n");
    fprintf(plot_file,"<< /Duplex true >> setpagedevice \n");
    fprintf(plot_file,"%\%\%\%EndSetup \n");
  }
  if (condition == 0)
  {
    fprintf(plot_file,"stroke \n");
    fprintf(plot_file,"showpage \n");
    fprintf(plot_file,"grestore \n");
    fprintf(plot_file,"%\%\%\%Trailer \n");
    fprintf(plot_file,"%\%\%\%EOF \n");
  }
  return;
}
/********************************************************************/
/*                                                                  */
/*     Newpage:  install code to cause page changing on output      */
/*                                                                  */
/*                                                                  */
void Newpage(FILE *plot_file,int *label, int *ordinal)
{
  fprintf(plot_file,"%\%\%\%Page: %i  %i \n",*label,*ordinal);
  fprintf(plot_file,"%\%\%\%BeginPageSetup \n");
  fprintf(plot_file,"%\%\%\%EndPageSetup \n");
  fprintf(plot_file," gsave \n");
  fprintf(plot_file," newpath \n");
  *ordinal = *ordinal + 1;
  *label   = *label   + 1;

  return;
}
/********************************************************************/
/*                                                                  */
/*     Endpage: terminates current page, used before Newpage        */
/*                                                                  */
/*                                                                  */

void Endpage(FILE *plot_file)
{
  fprintf(plot_file,"stroke \n");
  fprintf(plot_file,"showpage \n");
  fprintf(plot_file,"grestore \n");
  fprintf(plot_file,"%\%\%\%PageTrailer \n");
  return;
}
/********************************************************************/
/*                                                                  */
/*     Plot:  -move with pen down/up to desired coordintes          */
/*       num:  3 move with pen up   2 move with pen down            */
/*                                                                  */
void Plot(FILE *plot_file,float x, float y,int num)
{
  float x_plot = 0.0;
  float y_plot = 0.0;

  if (num == 3)
  {
    x_plot = x*PTS_PER_INCH*INCHES_PER_CM;
    y_plot = y*PTS_PER_INCH*INCHES_PER_CM;
    fprintf(plot_file,"%8.3f %8.3f pM\n",x_plot,y_plot);
  }
  if (num == 2)
  {
    x_plot = x*PTS_PER_INCH*INCHES_PER_CM;
    y_plot = y*PTS_PER_INCH*INCHES_PER_CM;
    fprintf(plot_file,"%8.3f %8.3f pL\n",x_plot,y_plot);
  } 
  return;
}
/********************************************************************/
/*                                                                  */
/*     PlotCircle:  plots circle                                    */
/*        Xor:  x-coord of centre (cm)                              */
/*        yor:  y-coord of centre (cm)                              */
/*        radius: radius (cm)                                       */
/*        pts:    number of points long circumference               */
/*        grey:   grey factor to plot line: 0: black  1: white      */
/*        fill:   no=0   yes=1                                      */
/*                                                                  */
void PlotCircle(FILE *plot_file,float Xor, float yor,
                           float radius, int pts,
                           float red,float green,float blue,
                           int fill)
{
  int i = 0;
  float xpt = 0.0;
  float ypt = 0.0;
  float azimuth = 0.0;

  fprintf(plot_file," stroke \n");
  fprintf(plot_file,"%4.2f %4.2f %4.2f setrgbcolor\n",red,green,blue);
  azimuth = 2.0*M_PI*((float)0)/((float)pts);
  xpt = Xor + radius*cos(azimuth);
  ypt = yor + radius*sin(azimuth);
  Plot(plot_file,xpt,ypt,3);
  for (i=0;i <= pts-1; i++)
  {
    azimuth = 2.0*M_PI*((float) i)/((float) pts);
    xpt = Xor + radius*cos(azimuth);
    ypt = yor + radius*sin(azimuth);
    Plot(plot_file,xpt,ypt,2);
  }
  fprintf(plot_file,"closepath\n");
  if (fill==1)
  {
    fprintf(plot_file,"fill\n");
  }
  fprintf(plot_file," stroke \n");

  return;
}
/********************************************************************/
/*                                                                  */
/*    PlotVector:  plot vector as x/y join the dots                 */
/*      x: vector containing x-coords                               */
/*      y: vector containing y-coords                               */
/*      n: number of points                                         */
/*      Xor:  x-coord of centre (cm)                                */
/*      yor:  y-coord of centre (cm)                                */
/*      pl:   length of box (cm)                                    */
/*      ph:   height of box (cm)                                    */
/*      red:  red component    0 <= red   <= 1                      */
/*      green: green component 0 <= green <= 1                      */
/*      blue : blue component  0 <= blue  <= 1                      */
/*                                                                  */
void PlotVector(FILE *plot_file,double *x, double *y,int n,
                double Xor,double yor,double pl,double ph,
                double red, double green, double blue,
                logical plot_grey,double grey,double linethickness,
                double x_min,double x_max,double y_min,double y_max)
{
   double xpt   = 0.0;
   double ypt   = 0.0;

   int i      = 0;

   if (plot_grey == TRUE_sn)
   {
     fprintf(plot_file,"%5.3f setgray \n",grey);
   }
   else
   {
     fprintf(plot_file,"%5.3f %5.3f %5.3f setrgbcolor \n",red,green,blue);
   }
   fprintf(plot_file,"%5.3f setlinewidth \n",linethickness);
   fprintf(plot_file," stroke \n");
   i = 0;
   xpt = Xor + pl*(x[i]-x_min)/(x_max-x_min);
   ypt = yor + ph*(y[i]-y_min)/(y_max-y_min);
   Plot(plot_file,xpt,ypt,3);
   for (i=0;i<n;i++)
   {
     xpt = Xor + pl*(x[i]-x_min)/(x_max-x_min);
     ypt = yor + ph*(y[i]-y_min)/(y_max-y_min);
     Plot(plot_file,xpt,ypt,2);
   }
   fprintf(plot_file," stroke \n");
   return;

}
/********************************************************************/
/*                                                                  */
/*    PlotBox: draw square box with optional of colouring in        */
/*       pt0:  pointer to double for 1st point: pt0[0] xcoord       */
/*                                              pt0[1] ycoord       */
/*       pt1:  pointer to double for 2nd point: pt1[0] xcoord       */
/*                                              pt1[1] ycoord       */
/*       fill: TRUE or FALSE                                        */
/*       red:  red component    0 <= red   <= 1                     */
/*       green: green component 0 <= green <= 1                     */
/*       blue : blue component  0 <= blue  <= 1                     */
/*       linewidth: line thickness (1/72 inch)                      */
/*       Xor:  x-coord of centre (cm)                               */
/*       yor:  y-coord of centre (cm)                               */
/*       pl:   length of box (cm)                                   */
/*       ph:   height of box (cm)                                   */
/*                                                                  */
void PlotBox(FILE *plot_file, double *pt0, double *pt1, double x_min,
             double x_max,double y_min,double y_max, logical fill,
             double red, double green, double blue, double linewidth,
             double Xor,double yor,double pl,double ph)
{
  double xpt  = 0.0;
  double ypt  = 0.0;

  fprintf(plot_file,"stroke \n");
  fprintf(plot_file,"%5.3f %5.3f %5.3f setrgbcolor \n",red,green,blue);
  fprintf(plot_file,"%5.3f setlinewidth \n",linewidth);
  fprintf(plot_file," stroke \n");
/*                                                      */
/*            first point                               */
  xpt = Xor + pl*(pt0[0]-x_min)/(x_max-x_min);
  ypt = yor + ph*(pt0[1]-y_min)/(y_max-y_min);
  Plot(plot_file,xpt,ypt,3);
/*                                                      */
/*            second point                              */
  xpt = Xor + pl*(pt1[0]-x_min)/(x_max-x_min);
  ypt = yor + ph*(pt0[1]-y_min)/(y_max-y_min);
  Plot(plot_file,xpt,ypt,2);
/*                                                      */
/*            third point                               */
  xpt = Xor + pl*(pt1[0]-x_min)/(x_max-x_min);
  ypt = yor + ph*(pt1[1]-y_min)/(y_max-y_min);
  Plot(plot_file,xpt,ypt,2);
/*                                                      */
/*            fourth point                              */
  xpt = Xor + pl*(pt0[0]-x_min)/(x_max-x_min);
  ypt = yor + ph*(pt1[1]-y_min)/(y_max-y_min);
  Plot(plot_file,xpt,ypt,2);
  fprintf(plot_file," closepath \n");
  if (fill == TRUE_sn)
  {
    fprintf(plot_file," fill \n");
  }
  return;
}
/********************************************************************/
/*                                                                  */
/*     ConvertHSVtoRGB -do rgb to hsv conversion, used to make      */
/*                      colour wheels                               */
/*       h:  hue                                                    */
/*       s:  saturation                                             */
/*       v:  brightness                                             */
/*       r:  red                                                    */      
/*       g:  green                                                  */
/*       b:  blue                                                   */
/*                                                                  */
/*                                                                  */
void ConvertHSVtoRGB(double *h,double *s,double *v,double *r,double *g,double *b)
{
  double h0           = 0.0;
  double s0           = 0.0;
  double v0           = 0.0;
  double m            = 0.0;
  double n            = 0.0;
  double k            = 0.0;
  double xi           = 0.0;
  double f            = 0.0;

  int    i            = 0;

  h0 = *h;
  s0 = *s;
  v0 = *v;
/*                                                                            */
/*                 use library function to convert RGB to HSV                 */
/*                                                                            */
  h0  = 6.0*h0;
  xi = (double)((int) h0);
  f  = h0 - xi;
  m  = v0*(1.0-s0);
  n  = v0*(1.0-s0*f);
  k  = v0*(1.0-s0*(1.0-f));
  i  = (int) xi;

  if (i == 0)
  {
   *r = v0;
   *g = k;
   *b = m;
  }
  if (i == 1)
  {
   *r = n;
   *g = v0;
   *b = m;
  }
  if (i == 2)
  {
   *r = m;
   *g = v0;
   *b = k;
  }
  if (i == 3)
  {
   *r = m;
   *g = n;
   *b = v0;
  }
  if (i == 4)
  {
   *r = k;
   *g = m;
   *b = v0;
  }
  if (i == 5)
  {
   *r = v0;
   *g = m;
   *b = n;
  }

  return;
}
/********************************************************************/
/*                                                                  */
/*     PlotNumber  -write number to file                            */
/*       height: text height, (1/72 inch)                           */
/*       angle: degrees                                             */
/*       xpt: x-coord (cm)                                          */
/*       ypt: y-coord (cm)                                          */
/*       number: number to write                                    */
/*       font: character font to use                                */
/*       red:  red component    0 <= red   <= 1                     */
/*       green: green component 0 <= green <= 1                     */
/*       blue : blue component  0 <= blue  <= 1                     */
/*       ndec: number of decimal places                             */
/*                                                                  */
/*                                                                  */
void PlotNumber(FILE *plot_file,double height,double angle,double xpt,
                double ypt,double number,char *font,double red,double green, double blue,int ndec)
{
   fprintf(plot_file,"%3.1f %3.1f %3.1f setrgbcolor\n",red,green,blue);
   Plot(plot_file,xpt,ypt,3);
   fprintf(plot_file,"%5.2f %2s \n",height,font);
   fprintf(plot_file,"%6.1f rotate \n",angle);
   if (ndec == 0)
   {
     fprintf(plot_file,"( %10.0f )\n",number);
   }
   else if (ndec == 1)
   {
     fprintf(plot_file,"( %10.1f )\n",number);
   }
   else if (ndec == 2)
   {
     fprintf(plot_file,"( %10.2f )\n",number);
   }
   else if (ndec == 3)
   {
     fprintf(plot_file,"( %10.3f )\n",number);
   }
   else
   {
     fprintf(plot_file,"( %10.4f )\n",number);
   }
   fprintf(plot_file,"show\n");
   fprintf(plot_file,"stroke \n");
   fprintf(plot_file,"%\%\n");
  return;
}
/********************************************************************/
/*                                                                  */
/*     PlotString  -write text string to file                       */
/*       height: text height, (1/72 inch)                           */
/*       angle: degrees                                             */
/*       xpt: x-coord (cm)                                          */
/*       ypt: y-coord (cm)                                          */
/*       string: character string to write                          */
/*       font: character font to use                                */
/*       red:  red component    0 <= red   <= 1                     */
/*       green: green component 0 <= green <= 1                     */
/*       blue : blue component  0 <= blue  <= 1                     */
/*                                                                  */
/*                                                                  */
void PlotString(FILE *plot_file,double height,double angle,double xpt,
                double ypt,char *string,char *font,double red,double green, double blue,int nchar)
{
   fprintf(plot_file,"%3.1f %3.1f %3.1f setrgbcolor\n",red,green,blue);
   Plot(plot_file,xpt,ypt,3);
   fprintf(plot_file,"%5.2f %2s \n",height,font);
   fprintf(plot_file,"%6.1f rotate \n",angle);
   if (nchar == 1)
   {
     fprintf(plot_file,"( %1s )\n",string);
   }
   else if (nchar == 2)
   {
     fprintf(plot_file,"( %2s )\n",string);
   }
   else if (nchar == 3)
   {
     fprintf(plot_file,"( %3s )\n",string);
   }
   else if (nchar == 4)
   {
     fprintf(plot_file,"( %4s )\n",string);
   }
   else if (nchar == 5)
   {
     fprintf(plot_file,"( %5s )\n",string);
   }
   else if (nchar == 6)
   {
     fprintf(plot_file,"( %6s )\n",string);
   }
   else if (nchar == 7)
   {
     fprintf(plot_file,"( %7s )\n",string);
   }
   else if (nchar == 8)
   {
     fprintf(plot_file,"( %8s )\n",string);
   }
   else if (nchar == 9)
   {
     fprintf(plot_file,"( %9s )\n",string);
   }
   else if (nchar == 10)
   {
     fprintf(plot_file,"( %10s )\n",string);
   }
   else if (nchar == 11)
   {
     fprintf(plot_file,"( %11s )\n",string);
   }
   else if (nchar == 12)
   {
     fprintf(plot_file,"( %12s )\n",string);
   }
   else if (nchar == 13)
   {
     fprintf(plot_file,"( %13s )\n",string);
   }
   else if (nchar == 14)
   {
     fprintf(plot_file,"( %14s )\n",string);
   }
   else if (nchar == 15)
   {
     fprintf(plot_file,"( %15s )\n",string);
   }
   else if (nchar == 16)
   {
     fprintf(plot_file,"( %16s )\n",string);
   }
   else
   {
     fprintf(plot_file,"( %17s )\n",string);
   }
   fprintf(plot_file,"show\n");
   fprintf(plot_file,"stroke \n");
   fprintf(plot_file,"%6.1f rotate \n",-angle);
   fprintf(plot_file,"stroke \n");
   fprintf(plot_file,"%\%\n");
  return;
}
/********************************************************************/
/*                                                                  */
/*     PlotCross -draw cross at location                            */
/*       xpt: x-coord (cm)                                          */
/*       ypt: y-coord (cm)                                          */
/*       linewidth:  line width in pts  (1/72 inch)                 */
/*       size: height (cm)                                          */
/*       red:  red component    0 <= red   <= 1                     */
/*       green: green component 0 <= green <= 1                     */
/*       blue : blue component  0 <= blue  <= 1                     */
/*                                                                  */
/*                                                                  */
void PlotCross(FILE *plot_file,double xpt, double ypt,double linewidth,double size,
               double red, double green, double blue)
{
  fprintf(plot_file,"stroke \n");
  fprintf(plot_file,"%5.3f %5.3f %5.3f setrgbcolor \n",red,green,blue);
  fprintf(plot_file,"%5.3f setlinewidth \n",linewidth);
  fprintf(plot_file," stroke \n");
/*                                                      */
  Plot(plot_file,xpt-size/2.0,ypt,3);
  Plot(plot_file,xpt+size/2.0,ypt,2);
  Plot(plot_file,xpt,ypt-size/2.0,3);
  Plot(plot_file,xpt,ypt+size/2.0,2);
  fprintf(plot_file," stroke \n");
  return;
}
/********************************************************************/
/*                                                                  */
/*     PlotTriangle -draw triangle at location                      */
/*       xpt: x-coord (cm)                                          */
/*       ypt: y-coord (cm)                                          */
/*       linewidth:  line width in pts  (1/72 inch)                 */
/*       size: height (cm)                                          */
/*       red:  red component    0 <= red   <= 1                     */
/*       green: green component 0 <= green <= 1                     */
/*       blue : blue component  0 <= blue  <= 1                     */
/*       fill : 0  no  1  yes                                       */
/*                                                                  */
/*                                                                  */
void PlotTriangle(FILE *plot_file,double xpt, double ypt,double linewidth,double size,
               double red, double green, double blue,int fill)
{
  double x1 = 0.0;
  double x2 = 0.0;
  double x3 = 0.0;
  double y1 = 0.0;
  double y2 = 0.0;
  double y3 = 0.0;
/*                                                      */
  fprintf(plot_file,"stroke \n");
  fprintf(plot_file,"%5.3f %5.3f %5.3f setrgbcolor \n",red,green,blue);
  fprintf(plot_file,"%5.3f setlinewidth \n",linewidth);
  fprintf(plot_file," stroke \n");
/*                                                      */
  y1 = ypt + 2.0*size/3.0;
  y2 = y1 - size;
  y3 = y2;
  x1 = xpt;
  x2 = x1 + 0.577350*size;
  x3 = x1 - 0.577350*size;
/*                                                      */
  Plot(plot_file,x1,y1,3);
  Plot(plot_file,x2,y2,2);
  Plot(plot_file,x3,y3,2);
  if (fill == 1)
  {
    fprintf(plot_file," closepath \n");
    fprintf(plot_file," fill\n");
  }
  fprintf(plot_file," stroke \n");
  return;
}
/********************************************************************/
/*                                                                  */
/*     PlotArrow -draw arrow at location                            */
/*       xpt: x-coord (cm)                                          */
/*       ypt: y-coord (cm)                                          */
/*       angle: degrees                                             */
/*       size: height (cm)                                          */
/*       red:  red component    0 <= red   <= 1                     */
/*       green: green component 0 <= green <= 1                     */
/*       blue : blue component  0 <= blue  <= 1                     */
/*                                                                  */
/*                                                                  */
void PlotArrow(FILE *plot_file,float xpt,float ypt,double angle,double size,
               double red, double green, double blue)
{
  float x = 0.0;
  float y = 0.0;

  x = 0.0;
  y = 0.0;
  fprintf(plot_file,"stroke\n");
  fprintf(plot_file,"%5.2f %5.2f %5.2f setrgbcolor\n",red,green,blue);
  fprintf(plot_file,"%6.3f %6.3f translate\n",xpt*PTS_PER_INCH*INCHES_PER_CM,
                                              ypt*PTS_PER_INCH*INCHES_PER_CM);
  fprintf(plot_file,"%5.2f rotate\n",angle);
  Plot(plot_file,x,y,3);
  Plot(plot_file,x-size*0.2,y,2);
  Plot(plot_file,x-size/10.0,y+size/3.0,2);
  Plot(plot_file,x,y+size,2);
  Plot(plot_file,x+size/10.0,y+size/3.0,2);
  Plot(plot_file,x+size*0.2,y,2);
  fprintf(plot_file,"closepath\n");
  fprintf(plot_file,"fill\n");
  fprintf(plot_file,"stroke\n");
  fprintf(plot_file,"%5.2f rotate\n",-angle);
  fprintf(plot_file,"%6.3f %6.3f translate\n",-xpt*PTS_PER_INCH*INCHES_PER_CM,
                                              -ypt*PTS_PER_INCH*INCHES_PER_CM);
  fprintf(plot_file,"stroke\n");
  return;
}

/********************************************************************/
/*                                                                  */
/*     ConvertRGBtoHSV -do hsv to rgb conversion                    */
/*                                                                  */
/*       h:  hue                                                    */
/*       s:  saturation                                             */
/*       v:  brightness                                             */
/*       r:  red                                                    */      
/*       g:  green                                                  */
/*       b:  blue                                                   */
/*                                                                  */
/*                                                                  */
#define N   10
#define M   5

void ConvertRGBtoHSV(double *H,double *S,double *V,double *R,double *G,double *B)
{
  double hlo  = 0.0;
  double slo  = 0.0; 
  double vlo  = 0.0; 
  double hhi  = 0.0;
  double shi  = 0.0; 
  double vhi  = 0.0; 
  double dn   = 0.0;
  double d    = 0.0;
  double dmin = 0.0;
  double h    = 0.0;
  double s    = 0.0;
  double v    = 0.0;
  double r    = 0.0;
  double g    = 0.0;
  double b    = 0.0;

  int i       = 0;
  int j       = 0;
  int k       = 0;
  int l       = 0;
  int imin    = 0;
  int jmin    = 0;
  int kmin    = 0;

  dn = 1.0/(double)(N-1);
  dmin = 9999999999.0;

  hlo = 0.0;
  hhi = 0.9999999;
  slo = 0.0;
  shi = 0.9999999;
  vlo = 0.0;
  vhi = 0.9999999;
  for (l=0;l<M;l++)
  {
    for (i=0;i<N;i++)
    {
      h = hlo + (hhi-hlo)*(double)i*dn;
      for (j=0;j<N;j++)
      {
        s = slo + (shi-slo)*(double)j*dn;
        for (k=0;k<N;k++)
        {
          v = vlo + (vhi-vlo)*(double)k*dn;
          ConvertHSVtoRGB(&h,&s,&v,&r,&g,&b);
          d = sqrt((r-*R)*(r-*R)+(g-*G)*(g-*G)+(b-*B)*(b-(*B)));
          if (d < dmin)
          {
            dmin = d;
            imin = i;
            jmin = j;
            kmin = k;
          }
        }
      }
    }
    *H = hlo + (hhi-hlo)*(double)imin*dn;
    *S = slo + (shi-slo)*(double)jmin*dn;
    *V = vlo + (vhi-vlo)*(double)kmin*dn;
    hlo = hlo + (hhi-hlo)*(double)(imin-1)*dn;
    hhi = hlo + (hhi-hlo)*(double)(imin+1)*dn;
    slo = slo + (shi-slo)*(double)(jmin-1)*dn;
    shi = slo + (shi-slo)*(double)(jmin+1)*dn;
    vlo = vlo + (vhi-vlo)*(double)(kmin-1)*dn;
    vhi = vlo + (vhi-vlo)*(double)(kmin+1)*dn;
    if (hlo<0.0)hlo=0.0;
    if (slo<0.0)slo=0.0;
    if (vlo<0.0)vlo=0.0;
    if (hhi>0.9999999)hhi=0.9999999;
    if (shi>0.9999999)shi=0.9999999;
    if (vhi>0.9999999)vhi=0.9999999;
  }
  return;
}
/********************************************************************/
/*                                                                  */
/*     HplotsBbox:  -initialize/terminate plot file                     */
/*       condition:  1 start  0 end                                 */
/*                                                                  */
/*                                                                  */
void HplotsBbox(FILE *plot_file,int condition,int llx,int lly,int urx,int ury)
{
  if (condition == 1)
  {
    fprintf(plot_file,"%\%!PS-Adobe-3.0\n");
    fprintf(plot_file,"%\%\%\%BoundingBox: %i %i %i %i \n",llx,lly,urx,ury);
    fprintf(plot_file,"%\%\%\%EndComments \n");
    fprintf(plot_file,"%\%\%\%BeginProlog \n");
    fprintf(plot_file,"%\%\%\%EndProlog \n");
    fprintf(plot_file,"%\%\%\%BeginSetup \n");
    fprintf(plot_file,"/pM  {stroke newpath moveto} def\n");
    fprintf(plot_file,"/pL  {lineto} def\n");
    fprintf(plot_file,"/hVB {/Helvetica-Bold findfont \n");
    fprintf(plot_file,"     exch scalefont setfont} def\n") ;
    fprintf(plot_file,"/hV  {/Helvetica findfont \n");
    fprintf(plot_file,"     exch scalefont setfont} def\n");
    fprintf(plot_file,"/cO  {/Courier findfont \n");
    fprintf(plot_file,"     exch scalefont setfont} def\n");
    fprintf(plot_file,"/fA {/Symbol findfont   \n");
    fprintf(plot_file,"      exch scalefont setfont} def\n");
    fprintf(plot_file,"<< /Duplex true >> setpagedevice \n");
    fprintf(plot_file,"%\%\%\%EndSetup \n");
  }
  if (condition == 0)
  {
    fprintf(plot_file,"stroke \n");
    fprintf(plot_file,"%\%\%\%Trailer \n");
    fprintf(plot_file,"%\%\%\%EOF \n");
  }
  return;
}
