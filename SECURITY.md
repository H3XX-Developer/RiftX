# Security Policy

## 🔐 Reporting a Vulnerability

**Do NOT open a public GitHub issue for security problems.**

If you find a security issue with RiftX — anything from download tampering
to installer bypass — please report it **privately** so it can be fixed
before anyone else can exploit it.

### How to report

1. **Join the RiftX Discord** — [PASTE_DISCORD_LINK_HERE](PASTE_DISCORD_LINK_HERE)
2. **Go to the `#security-report` channel**
3. **Open a ticket** using the form provided
4. **Fill out the form** with:
   - What you found (short title)
   - Steps to reproduce
   - Impact (what could an attacker do?)
   - Which version of RiftX you tested
   - Suggested fix (optional — but very welcome)
   - Your Discord username (for follow-up questions)

### What happens next

- 📩 **Reports are reviewed on weekends** (solo dev — weekdays are for real life)
- ✅ **You'll get a reply** within 7 days
- ✅ **Confirmed issues are fixed** before public disclosure
- ✅ **Credit given** to the reporter if you want it
- 🚫 **Please don't share the issue publicly** until it's patched

---

## 🎯 Scope

### In scope

These are the kinds of issues I want to hear about:

- 🔓 **Download tampering** — modifying a file in transit
- 🔓 **Hash verification bypass** — making a bad file pass the SHA-256 check
- 🔓 **Installer path traversal** — writing files outside `Hdd:\RiftX\`
- 🔓 **Cache poisoning** — injecting malicious data into the catalog cache
- 🔓 **Catalog injection** — tricking the launcher into loading a bad catalog
- 🔓 **Code execution** — any way to run arbitrary code through RiftX
- 🔓 **Privilege escalation** — anything beyond what RiftX should be able to do

### Out of scope

These are **not** security issues in RiftX itself:

- ❌ **Social engineering** — someone tricking you into running something
- ❌ **Physical console access** — someone with your Xbox in hand
- ❌ **Third-party homebrew** — issues in apps you installed *through* RiftX
- ❌ **Xbox Live bans** — that's a risk of homebrew, not a RiftX bug
- ❌ **Modding risks** — mods in online games can get you banned
- ❌ **Your own misconfiguration** — wrong URL, corrupted SD card, etc.

---

## 🛡️ What RiftX Already Does for Security

So you know what's already in place before reporting:

- ✅ **SHA-256 verification** — every download is hashed and checked
- ✅ **Sandboxed installs** — only touches `Hdd:\RiftX\`
- ✅ **No telemetry** — nothing is sent anywhere except catalog fetches
- ✅ **No accounts** — no credentials to steal
- ✅ **No external dependencies** — everything embedded in the XEX
- ✅ **Open catalog** — anyone can inspect the JSON catalog

If you find a way to break any of these, that's a bug worth reporting.

---

## 📜 Disclosure Policy

- 📩 **Report privately first** via Discord ticket
- ⏳ **Give time to fix** — no rushing, but weekends only
- ✅ **Public disclosure** happens after the fix is shipped
- 🏆 **Reporter credit** given (or anonymous if preferred)
- 🚫 **No bug bounties** — this is a free solo project, not a company
- 🚫 **No legal threats** — responsible disclosure only

---

## 🙏 Thank You

Security researchers and curious users who report issues help make RiftX
safer for everyone. Even small reports matter.

If you're unsure whether something counts as a security issue, **report it
anyway** — better safe than sorry.

---

## 📞 Quick Links

- 💬 **Discord** — [PASTE_DISCORD_LINK_HERE](PASTE_DISCORD_LINK_HERE)
- 📋 **Report form** — `#security-report` channel
- 🏠 **Main repo** — right here
- ⚠️ **Not open source** — no source code review possible

---

*RiftX is a solo project developed by H3XX-Dev. Security reports are taken
seriously and handled as fast as possible — usually on weekends.*
