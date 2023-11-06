import flask
from flask import request, jsonify
from transformers import AutoTokenizer, GPT2LMHeadModel

app = flask.Flask(__name__)

tokenizer = AutoTokenizer.from_pretrained("gpt2")
model = GPT2LMHeadModel.from_pretrained("gpt2", pad_token_id=tokenizer.eos_token_id)

@app.route('/generate', methods=['POST'])
def generate_text():
    content = request.json
    input_text = content['text']
    input_ids = tokenizer.encode(input_text, return_tensors='pt')

    beam_output = model.generate(
        input_ids,
        max_length=content.get('max_length', 200),
        num_beams=content.get('num_beams', 5),
        no_repeat_ngram_size=content.get('no_repeat_ngram_size', 2),
        early_stopping=True
    )

    output = tokenizer.decode(beam_output[0], skip_special_tokens=True)
    return jsonify({"result": output})

if __name__ == '__main__':
    app.run(debug=True, port=5000)
