{
  "targets": [
    {
      "target_name": "hmac",
      "sources": [
        "hmac.cpp"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
