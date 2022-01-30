#from libs import requests
import sys, os
sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)),'./libs/'))
import requests

class GoogleDriveUtils:
    
    @staticmethod
    def download_sheet(doc_url, doc_format="csv", store_in_file=False):
        '''Downloads the GDrive Spreadsheet stored in the given url, and returns its content in string format
        If store_in_file is True, it returns the path for a file. Note: it's meant to be a temporary file, and should be deleted'''
        doc_id = doc_url.split("/d/")[1].split("/")[0]
        sheet_id = doc_url.split("gid=")[1]
        csv_url='https://docs.google.com/spreadsheets/d/{1}/export?format={0}&id={1}&gid={2}'.format(doc_format, doc_id, sheet_id)
        res=requests.get(url=csv_url)
        
        if store_in_file:
            script_folder = os.path.dirname(os.path.realpath(__file__))
            temp_file_full_name = '{0}\\{1}.csv'.format(script_folder, doc_id)
            temp_file =  open(temp_file_full_name, 'wb')
            temp_file.write(res.content)
            temp_file.close()
            
            return temp_file_full_name
        
        return str(res.content)
        
    