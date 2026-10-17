# Adding a Language to RiftX

RiftX ships with 9 languages. Here's how to add another.

## Prerequisites

- A valid **2-letter language code** (ISO 639-1)
  - Examples: `ko` (Korean), `ar` (Arabic), `hi` (Hindi)
- A **UTF-8 text editor** (VS Code, Notepad++)

## Step-by-step

### 1. Copy the English file

Copy `client/source/resources/lang/en.json` to
`client/source/resources/lang/xx.json` (where `xx` is the new code).

### 2. Translate every value

Open `xx.json` and translate each value. **Do not translate keys** —
they must stay exactly the same so the loader finds them.

Example for Korean (`ko.json`):

```json
{
  "app_name": "RiftX",
  "loading": "로딩 중...",
  "install": "설치",
  ...
}
