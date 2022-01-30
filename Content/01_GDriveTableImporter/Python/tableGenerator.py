import unreal
import sys, os
sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)),'./libs/'))
import importlib

from gDriveUtils import GoogleDriveUtils as GDU

class CantCreateAsset(Exception):
    pass
    
class CantReloadAsset(Exception):
    pass

class TableGenerator:
    '''Class that can generate DataTables and StringTables in UE4'''
    
    '''----------------------------------------Create empty tables-----------------------------------------'''
    def create_empty_string_table(self):
        asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
        asset = asset_tools.create_asset_with_dialog("", "/Game/", None, unreal.StringTableFactory())
        
        if asset is None:
            raise CantCreateAsset("Couldn't create StringTable")
        
        unreal.log("StringTable '{0}' has been created".format(asset.get_path_name()))
        return asset
        
    def create_empty_data_table(self):
        asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
        asset = asset_tools.create_asset_with_dialog("", "/Game/", unreal.DataTable, unreal.DataTableFactory())
        
        if asset is None:
            raise CantCreateAsset("Couldn't create DataTable")
            
        unreal.log("DataTable '{0}' has been created".format(asset.get_path_name()))
        return asset
        
    '''-----------------------------------    Utility functions   ------------------------------------------'''           
    def is_string_table(self, asset):
        return asset.__class__ == unreal.StringTable

    '''-----------------------------------    Reimport functions   ------------------------------------------'''
    def reimport_asset(self, doc_url, asset):
        if self.is_string_table(asset):
            self.reimport_stringtable_from_gdrive(doc_url, asset)
        else:
            self.reimport_datatable_from_gdrive(doc_url, asset)
            
    def reimport_datatable_from_gdrive(self, doc_url, asset):
        sheet_content = GDU.download_sheet(doc_url)
        sheet_content_cleaned = sheet_content.replace("\\r\\n", "\n") #In memory, I need to replace the \r. Stored in temp file wouldn't be necessary
        if not unreal.DataTableFunctionLibrary.fill_data_table_from_csv_string(asset, sheet_content_cleaned):
            raise CantReloadAsset ("There was a problem filling the DataTable")
        
        self.register_imported_table(asset, doc_url)
        unreal.EditorAssetLibrary.save_loaded_asset(asset)
            
    def reimport_stringtable_from_gdrive(self, doc_url, asset):
        temp_file_full_name = GDU.download_sheet(doc_url, store_in_file=True)        
        ts = unreal.get_editor_subsystem(unreal.TableSubsystem)
        
        result = ts.import_string_table_from_csv(asset, temp_file_full_name)
        
        try:
            if os.path.exists(temp_file_full_name):
               os.remove(temp_file_full_name)
        except:
            unreal.log("WARNING: Temp file {0} couldn't be removed").format(temp_file_full_name)
        
        if not result:
            raise CantReloadAsset ("There was a problem filling the StringTable")
            
        self.register_imported_table(asset, doc_url)
        
        unreal.EditorAssetLibrary.save_loaded_asset(asset)

    '''-----------------------------------    Create functions   -----------------------------------'''            
    def create_asset_from_gdrive(self, doc_url, is_string_table):
        if is_string_table:
            self.create_string_table_from_gdrive(doc_url)
        else:
            self.create_data_table_from_gdrive(doc_url)
        
    
    def create_string_table_from_gdrive(self, doc_url):
        asset = self.create_empty_string_table()
        self.reimport_stringtable_from_gdrive(doc_url, asset)
            
        
    def create_data_table_from_gdrive(self, doc_url):
        asset = self.create_empty_data_table()
        self.reimport_datatable_from_gdrive(doc_url, asset)

    '''----------------------------------- TableRegistry functions-----------------------------------'''

    def register_imported_table(self, asset, doc_url):
    
        if (asset is None):
            unreal.log("TableGenerator: asset was Null")
            return

        table_subsystem = unreal.TableSubsystem()
        table_registry = table_subsystem.find_table_registry()
        
        if table_registry.does_table_exist(asset):
            old_table_info = table_registry.get_table_info(asset)
            old_table_info.url = doc_url
            table_registry.modify_table_info(asset, old_table_info) 
        else:      
            table_info = unreal.TableInfo()
            table_info.url = doc_url
            table_info.categories.add("All")
            if self.is_string_table(asset):
                table_info.categories.add("StringTables")
            else:
                table_info.categories.add("DataTables")

            table_registry.add_table(asset, table_info)
            
        unreal.EditorAssetLibrary.save_loaded_asset(table_registry, False)
            



if __name__ == "__main__":
    tg = TableGenerator()
    #tg.create_string_table_from_gdrive('https://docs.google.com/spreadsheets/d/1iDrRYVRqN7GQFaPOLYU5TxQJizE7brVUPBcVwkqpyWQ/edit#gid=0')