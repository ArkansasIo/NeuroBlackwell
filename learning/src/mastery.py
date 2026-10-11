from dataclasses import dataclass,field
from .scoring import expected_correctness
@dataclass
class SkillState:
    mastery:float=0.0; attempts:int=0; correct:int=0; last_difficulty:float=0.0; transfer_score:float=0.0; error_count:int=0
    @property
    def accuracy(self): return self.correct/self.attempts if self.attempts else 0.0
@dataclass
class MasteryModel:
    learning_rate:float=0.35; skills:dict[str,SkillState]=field(default_factory=dict)
    def state(self,skill): return self.skills.setdefault(skill,SkillState())
    def update(self,skill,difficulty,correct,transfer=0.0,error=False):
        s=self.state(skill); p=expected_correctness(s.mastery,difficulty); s.mastery+=self.learning_rate*((1 if correct else 0)-p); s.attempts+=1; s.correct+=int(correct); s.error_count+=int(error or not correct); s.last_difficulty=float(difficulty); s.transfer_score+=max(0,min(1,float(transfer))); return s
    def ready_for(self,skill,difficulty,threshold=0.75): return expected_correctness(self.state(skill).mastery,difficulty)>=threshold
