import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore
from google.cloud import bigquery
import json
from dotenv import load_dotenv
import os 


load_dotenv()
CREDENTIAL_PATH = os.getenv("CREDENTIAL_PATH")
os.environ['GOOGLE_APPLICATION_CREDENTIALS'] = CREDENTIAL_PATH
BQ_TABLE_ID = os.getenv("BQ_TABLE_ID")
FIRESTORE_DB = os.getenv("FIRESTORE_DB")


if not firebase_admin._apps:
    cred = credentials.Certificate(CREDENTIAL_PATH)
    app = firebase_admin.initialize_app(cred)
    db = firestore.client()
else:
    pass

users_ref = db.collection(FIRESTORE_DB)
docs = users_ref.stream()

docList = []
for doc in docs:
    print(f"{doc.id} => {doc.to_dict()}")
    docList.append(doc.to_dict())
    
client = bigquery.Client()
errors = client.insert_rows_json(BQ_TABLE_ID, docList)
if errors == []:
    print('New rows have been added.')
else:
    print(f'Encountered errors while inserting rows: {errors}')
