#!/usr/bin/python
import cgi

form = cgi.FieldStorage()

param1 = form.getvalue('param1')
param2 = form.getvalue('param2')

if param1 and param2:
    print("Value of param1: " + param1 + "<br>")
    print("Value of param2: " + param2 + "<br>")
else:
    print("One or both parameters are missing in the query string.")
