#!/usr/bin/python3

import os
import cgi
import shutil

form = cgi.FieldStorage()

# Retrieve the filename from the form data
item_to_delete = form.getvalue('filename')

# Define the base directory
base_directory = os.path.join(os.getcwd(), 'www', 'serverDB')

if item_to_delete is None:
    message = 'No file or directory name provided.'
else:
    # Construct the full path to the file or directory
    item_path = os.path.join(base_directory, item_to_delete)
    
    if os.path.exists(item_path):
        try:
            if os.path.isdir(item_path):
                shutil.rmtree(item_path)
                message = f'The directory "{item_to_delete}" has been successfully deleted.'
            else:
                os.remove(item_path)
                message = f'The file "{item_to_delete}" has been successfully deleted.'
        except Exception as e:
            message = f'Error deleting "{item_to_delete}": {e}'
    else:
        message = f'File or directory "{item_to_delete}" does not exist.'

# Output the result
print("Content-Type: text/html;charset=utf-8\r\n")
print()
print("<html><body>")
print(f"<h1>{message}</h1>")
print("</body></html>")

