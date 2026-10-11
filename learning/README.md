# Synthetic Human Brain Program — Learning & Cognitive Benchmark

Adaptive curriculum and synthetic practice tasks for evaluating a simulated learner. Curriculum levels: kindergarten, elementary, middle school, high school, college, university, and graduate/research.

Tracks accuracy, mastery, working memory, reasoning, transfer, retention, response time, and error categories separately. This is a research benchmark, **not a validated clinical IQ test**.

## Files and directories

- `data/curriculum.json`: level progression and learning objectives.
- `data/subjects.json`: subject catalogue.
- `data/question_bank.json`: core sample questions.
- `data/elementary_set_01.json`: 20 additional elementary questions across subjects.
- `schema/`: question and assessment-result JSON schemas.
- `src/`: adaptive selection, scoring, mastery, memory, and generation logic.
- `tests/`: unit tests.
- `tools/generate_curriculum_workbook.py`: Excel workbook generation.

Questions in the added set are synthetic examples, not standardized or normed assessment items. Review answer normalization and curriculum alignment before using them to evaluate real students.
