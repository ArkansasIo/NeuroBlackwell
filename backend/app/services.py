import os

def health():
    return {'status':'ok','service':'neuroblackwell-api','database_configured':bool(os.getenv('DATABASE_URL') or os.getenv('DB_DSN'))}
