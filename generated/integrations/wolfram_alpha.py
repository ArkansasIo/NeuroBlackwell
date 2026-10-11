"""Optional Wolfram|Alpha API adapter.

Set WOLFRAMALPHA_APP_ID in the environment. Never commit the App ID.
This adapter returns API results as references; it does not mirror the Wolfram database.
"""
import os
import urllib.parse
import urllib.request
import xml.etree.ElementTree as ET

API_URL = "https://api.wolframalpha.com/v2/query"

class WolframAlphaError(RuntimeError):
    pass

def query(expression: str, timeout: float = 15.0) -> dict:
    app_id = os.getenv("WOLFRAMALPHA_APP_ID")
    if not app_id:
        raise WolframAlphaError("Set WOLFRAMALPHA_APP_ID to enable Wolfram|Alpha queries")
    if not expression.strip():
        raise ValueError("expression must not be empty")
    params = urllib.parse.urlencode({"appid": app_id, "input": expression, "format": "plaintext", "output": "XML"})
    request = urllib.request.Request(API_URL + "?" + params, headers={"User-Agent": "NeuroBlackwell/0.1"})
    try:
        with urllib.request.urlopen(request, timeout=timeout) as response:
            root = ET.fromstring(response.read())
    except Exception as exc:
        raise WolframAlphaError(f"Wolfram|Alpha request failed: {exc}") from exc
    pods = []
    for pod in root.findall(".//pod"):
        texts = [el.text or "" for el in pod.findall(".//plaintext")]
        if texts:
            pods.append({"title": pod.attrib.get("title", ""), "text": "\n".join(texts)})
    return {"success": root.attrib.get("success") == "true", "expression": expression, "pods": pods}
