import os
from sqlalchemy import create_engine

DATABASE_URL=os.getenv('DATABASE_URL','sqlite:///./neuroblackwell.db')
engine=create_engine(DATABASE_URL,pool_pre_ping=True)
