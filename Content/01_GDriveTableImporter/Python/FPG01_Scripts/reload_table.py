import tableGenerator as TG
import importlib
import gDriveUtils as GDU

importlib.reload(TG)
importlib.reload(GDU)
instance = TG.TableGenerator()
instance.reimport_asset(doc_url, asset)