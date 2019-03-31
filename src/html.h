#ifndef __HTML_H__
#define __HTML_H__

string top_section = R"(<!DOCTYPE html>
<html>

<head>
   <meta charset="UTF-8">
   <title>title</title>
   <style>
       h2 {
           font-family: arial, sans-serif;
       }
      
       table {
           font-family: arial, sans-serif;
           border-collapse: collapse;
           width: 100%;
           border-radius: 25px;
           width: 65%;
       }
      
       td,
       th {
           border: 1px solid #dddddd;
           text-align: left;
           padding: 8px;
       }
      
       tr:nth-child(even) {
           background-color: #dddddd;
       }
   </style>
</head>

<body>
   <center>)";

string body = R"(
       <table>
           <tr>
               <th>Process Name</th>
               <th>Memory Range Found</th>
               <th>Result</th>
           </tr>
           <br>
           <tr>)";

string footer = R"(           </tr>
       </table>
   </center>
</body>

</html>)";

#endif