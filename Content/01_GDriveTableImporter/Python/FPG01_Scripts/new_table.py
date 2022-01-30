import tableGenerator as TG
import importlib
import gDriveUtils as GDU

importlib.reload(TG)
importlib.reload(GDU)
instance = TG.TableGenerator()
instance.create_asset_from_gdrive(doc_url, is_string_table)