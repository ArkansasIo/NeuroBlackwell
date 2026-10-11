from dataclasses import dataclass
from .mastery import MasteryModel
from .memory_model import MemoryModel
@dataclass
class AssessmentEngine:
    questions:list[dict]; mastery:MasteryModel|None=None; memory:MemoryModel|None=None
    def __post_init__(self): self.mastery=self.mastery or MasteryModel(); self.memory=self.memory or MemoryModel()
    def select_next(self,level=None,subject=None,target_difficulty=None):
        c=[q for q in self.questions if (level is None or q['level']==level) and (subject is None or q['subject']==subject)]
        if not c: raise LookupError('No questions match requested filters')
        target_difficulty=target_difficulty if target_difficulty is not None else sum(q['difficulty'] for q in c)/len(c)
        return min(c,key=lambda q:(abs(q['difficulty']-target_difficulty),self.mastery.state(q['skill']).attempts,q['id']))
    def submit(self,question,answer,now_day=0.0,response_time_ms=None,transfer=0.0,error_category=None):
        correct=str(answer).strip().lower()==str(question['answer']).strip().lower(); s=self.mastery.update(question['skill'],question['difficulty'],correct,transfer,error=not correct); r=self.memory.retrieve(question['skill'],now_day,correct)
        return {'question_id':question['id'],'correct':correct,'mastery':s.mastery,'accuracy':s.accuracy,'retention_before':r,'response_time_ms':response_time_ms,'transfer':transfer,'error_category':error_category}
    def level_recommendation(self,current_level):
        order=['kindergarten','elementary','middle_school','high_school','college','university','graduate_research']; i=order.index(current_level); return order[min(i+1,len(order)-1)]
