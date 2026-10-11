from learning.src.memory_model import MemoryModel
def test_successful_retrieval_strengthens_memory():
 m=MemoryModel(); m.retrieve('x',0,True); assert m.retention('x',0)>0; m.retrieve('x',1,True); assert m.traces['x'].successful_retrievals==2
