#ifndef CAPTIVE_PORTAL_H
#define CAPTIVE_PORTAL_H

const char *captive_portal_html = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Wifi Manager</title>
  <style>@layer properties{@supports (((-webkit-hyphens:none)) and (not (margin-trim:inline))) or ((-moz-orient:inline) and (not (color:rgb(from red r g b)))){*,:before,:after,::backdrop{--tw-rotate-x:initial;--tw-rotate-y:initial;--tw-rotate-z:initial;--tw-skew-x:initial;--tw-skew-y:initial;--tw-space-y-reverse:0;--tw-space-x-reverse:0;--tw-border-style:solid;--tw-leading:initial;--tw-font-weight:initial;--tw-tracking:initial;--tw-shadow:0 0 #0000;--tw-shadow-color:initial;--tw-shadow-alpha:100%;--tw-inset-shadow:0 0 #0000;--tw-inset-shadow-color:initial;--tw-inset-shadow-alpha:100%;--tw-ring-color:initial;--tw-ring-shadow:0 0 #0000;--tw-inset-ring-color:initial;--tw-inset-ring-shadow:0 0 #0000;--tw-ring-inset:initial;--tw-ring-offset-width:0px;--tw-ring-offset-color:#fff;--tw-ring-offset-shadow:0 0 #0000;--tw-backdrop-blur:initial;--tw-backdrop-brightness:initial;--tw-backdrop-contrast:initial;--tw-backdrop-grayscale:initial;--tw-backdrop-hue-rotate:initial;--tw-backdrop-invert:initial;--tw-backdrop-opacity:initial;--tw-backdrop-saturate:initial;--tw-backdrop-sepia:initial;--tw-ease:initial}}}@layer theme{:root,:host{--font-sans:ui-sans-serif, system-ui, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol", "Noto Color Emoji";--font-mono:ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace;--color-red-50:oklch(97.1% .013 17.38);--color-red-200:oklch(88.5% .062 18.334);--color-red-500:oklch(63.7% .237 25.331);--color-red-600:oklch(57.7% .245 27.325);--color-red-700:oklch(50.5% .213 27.518);--color-black:#000;--color-white:#fff;--spacing:.25rem;--text-xs:.75rem;--text-xs--line-height:calc(1 / .75);--text-sm:.875rem;--text-sm--line-height:calc(1.25 / .875);--font-weight-medium:500;--font-weight-semibold:600;--tracking-tight:-.025em;--tracking-widest:.1em;--leading-relaxed:1.625;--radius-sm:.25rem;--radius-md:.375rem;--radius-lg:.5rem;--radius-xl:.75rem;--ease-in-out:cubic-bezier(.4, 0, .2, 1);--animate-spin:spin 1s linear infinite;--animate-pulse:pulse 2s cubic-bezier(.4, 0, .6, 1) infinite;--blur-sm:8px;--default-transition-duration:.15s;--default-transition-timing-function:cubic-bezier(.4, 0, .2, 1);--default-font-family:var(--font-sans);--default-mono-font-family:var(--font-mono)}}@layer base{*,:after,:before,::backdrop{box-sizing:border-box;border:0 solid;margin:0;padding:0}::file-selector-button{box-sizing:border-box;border:0 solid;margin:0;padding:0}html,:host{-webkit-text-size-adjust:100%;tab-size:4;line-height:1.5;font-family:var(--default-font-family,ui-sans-serif, system-ui, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol", "Noto Color Emoji");font-feature-settings:var(--default-font-feature-settings,normal);font-variation-settings:var(--default-font-variation-settings,normal);-webkit-tap-highlight-color:transparent}hr{height:0;color:inherit;border-top-width:1px}abbr:where([title]){-webkit-text-decoration:underline dotted;text-decoration:underline dotted}h1,h2,h3,h4,h5,h6{font-size:inherit;font-weight:inherit}a{color:inherit;-webkit-text-decoration:inherit;-webkit-text-decoration:inherit;-webkit-text-decoration:inherit;text-decoration:inherit}b,strong{font-weight:bolder}code,kbd,samp,pre{font-family:var(--default-mono-font-family,ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace);font-feature-settings:var(--default-mono-font-feature-settings,normal);font-variation-settings:var(--default-mono-font-variation-settings,normal);font-size:1em}small{font-size:80%}sub,sup{vertical-align:baseline;font-size:75%;line-height:0;position:relative}sub{bottom:-.25em}sup{top:-.5em}table{text-indent:0;border-color:inherit;border-collapse:collapse}:-moz-focusring{outline:auto}progress{vertical-align:baseline}summary{display:list-item}ol,ul,menu{list-style:none}img,svg,video,canvas,audio,iframe,embed,object{vertical-align:middle;display:block}img,video{max-width:100%;height:auto}button,input,select,optgroup,textarea{font:inherit;font-feature-settings:inherit;font-variation-settings:inherit;letter-spacing:inherit;color:inherit;opacity:1;background-color:#0000;border-radius:0}::file-selector-button{font:inherit;font-feature-settings:inherit;font-variation-settings:inherit;letter-spacing:inherit;color:inherit;opacity:1;background-color:#0000;border-radius:0}:where(select:is([multiple],[size])) optgroup{font-weight:bolder}:where(select:is([multiple],[size])) optgroup option{padding-inline-start:20px}::file-selector-button{margin-inline-end:4px}::placeholder{opacity:1}@supports (not ((-webkit-appearance:-apple-pay-button))) or (contain-intrinsic-size:1px){::placeholder{color:currentColor}@supports (color:color-mix(in lab, red, red)){::placeholder{color:color-mix(in oklab, currentcolor 50%, transparent)}}}textarea{resize:vertical}::-webkit-search-decoration{-webkit-appearance:none}::-webkit-date-and-time-value{min-height:1lh;text-align:inherit}::-webkit-datetime-edit{display:inline-flex}::-webkit-datetime-edit-fields-wrapper{padding:0}::-webkit-datetime-edit{padding-block:0}::-webkit-datetime-edit-year-field{padding-block:0}::-webkit-datetime-edit-month-field{padding-block:0}::-webkit-datetime-edit-day-field{padding-block:0}::-webkit-datetime-edit-hour-field{padding-block:0}::-webkit-datetime-edit-minute-field{padding-block:0}::-webkit-datetime-edit-second-field{padding-block:0}::-webkit-datetime-edit-millisecond-field{padding-block:0}::-webkit-datetime-edit-meridiem-field{padding-block:0}:-moz-ui-invalid{box-shadow:none}button,input:where([type=button],[type=reset],[type=submit]){appearance:button}::file-selector-button{appearance:button}::-webkit-inner-spin-button{height:auto}::-webkit-outer-spin-button{height:auto}[hidden]:where(:not([hidden=until-found])){display:none!important}}@layer components;@layer utilities{.absolute{position:absolute}.fixed{position:fixed}.relative{position:relative}.inset-0{inset:calc(var(--spacing) * 0)}.inset-x-0{inset-inline:calc(var(--spacing) * 0)}.top-0{top:calc(var(--spacing) * 0)}.top-2{top:calc(var(--spacing) * 2)}.top-2\.5{top:calc(var(--spacing) * 2.5)}.right-3{right:calc(var(--spacing) * 3)}.left-0{left:calc(var(--spacing) * 0)}.z-0{z-index:0}.z-10{z-index:10}.z-50{z-index:50}.mt-0{margin-top:calc(var(--spacing) * 0)}.mt-0\.5{margin-top:calc(var(--spacing) * .5)}.mt-1{margin-top:calc(var(--spacing) * 1)}.mt-2{margin-top:calc(var(--spacing) * 2)}.mt-4{margin-top:calc(var(--spacing) * 4)}.mb-1{margin-bottom:calc(var(--spacing) * 1)}.mb-3{margin-bottom:calc(var(--spacing) * 3)}.mb-4{margin-bottom:calc(var(--spacing) * 4)}.mb-5{margin-bottom:calc(var(--spacing) * 5)}.mb-6{margin-bottom:calc(var(--spacing) * 6)}.flex{display:flex}.hidden{display:none}.table{display:table}.h-0{height:calc(var(--spacing) * 0)}.h-0\.5{height:calc(var(--spacing) * .5)}.h-1{height:calc(var(--spacing) * 1)}.h-2{height:calc(var(--spacing) * 2)}.h-3{height:calc(var(--spacing) * 3)}.h-3\.5{height:calc(var(--spacing) * 3.5)}.h-4{height:calc(var(--spacing) * 4)}.h-5{height:calc(var(--spacing) * 5)}.h-6{height:calc(var(--spacing) * 6)}.h-10{height:calc(var(--spacing) * 10)}.h-12{height:calc(var(--spacing) * 12)}.h-14{height:calc(var(--spacing) * 14)}.h-full{height:100%}.h-screen{height:100vh}.max-h-full{max-height:100%}.min-h-0{min-height:calc(var(--spacing) * 0)}.w-1{width:calc(var(--spacing) * 1)}.w-1\/3{width:33.3333%}.w-2{width:calc(var(--spacing) * 2)}.w-3{width:calc(var(--spacing) * 3)}.w-3\.5{width:calc(var(--spacing) * 3.5)}.w-4{width:calc(var(--spacing) * 4)}.w-5{width:calc(var(--spacing) * 5)}.w-6{width:calc(var(--spacing) * 6)}.w-12{width:calc(var(--spacing) * 12)}.w-24{width:calc(var(--spacing) * 24)}.w-full{width:100%}.max-w-\[340px\]{max-width:340px}.flex-1{flex:1}.shrink-0{flex-shrink:0}.transform{transform:var(--tw-rotate-x,) var(--tw-rotate-y,) var(--tw-rotate-z,) var(--tw-skew-x,) var(--tw-skew-y,)}.animate-\[slide_1s_ease-in-out_infinite\]{animation:1s ease-in-out infinite slide}.animate-pulse{animation:var(--animate-pulse)}.animate-spin{animation:var(--animate-spin)}.cursor-pointer{cursor:pointer}.flex-col{flex-direction:column}.items-center{align-items:center}.items-start{align-items:flex-start}.justify-between{justify-content:space-between}.justify-center{justify-content:center}.gap-1{gap:calc(var(--spacing) * 1)}.gap-1\.5{gap:calc(var(--spacing) * 1.5)}.gap-2{gap:calc(var(--spacing) * 2)}.gap-3{gap:calc(var(--spacing) * 3)}.gap-6{gap:calc(var(--spacing) * 6)}:where(.space-y-1>:not(:last-child)){--tw-space-y-reverse:0;margin-block-start:calc(calc(var(--spacing) * 1) * var(--tw-space-y-reverse));margin-block-end:calc(calc(var(--spacing) * 1) * calc(1 - var(--tw-space-y-reverse)))}:where(.space-y-1\.5>:not(:last-child)){--tw-space-y-reverse:0;margin-block-start:calc(calc(var(--spacing) * 1.5) * var(--tw-space-y-reverse));margin-block-end:calc(calc(var(--spacing) * 1.5) * calc(1 - var(--tw-space-y-reverse)))}:where(.space-y-3>:not(:last-child)){--tw-space-y-reverse:0;margin-block-start:calc(calc(var(--spacing) * 3) * var(--tw-space-y-reverse));margin-block-end:calc(calc(var(--spacing) * 3) * calc(1 - var(--tw-space-y-reverse)))}:where(.space-y-4>:not(:last-child)){--tw-space-y-reverse:0;margin-block-start:calc(calc(var(--spacing) * 4) * var(--tw-space-y-reverse));margin-block-end:calc(calc(var(--spacing) * 4) * calc(1 - var(--tw-space-y-reverse)))}:where(.space-x-1\.5>:not(:last-child)){--tw-space-x-reverse:0;margin-inline-start:calc(calc(var(--spacing) * 1.5) * var(--tw-space-x-reverse));margin-inline-end:calc(calc(var(--spacing) * 1.5) * calc(1 - var(--tw-space-x-reverse)))}:where(.space-x-2>:not(:last-child)){--tw-space-x-reverse:0;margin-inline-start:calc(calc(var(--spacing) * 2) * var(--tw-space-x-reverse));margin-inline-end:calc(calc(var(--spacing) * 2) * calc(1 - var(--tw-space-x-reverse)))}:where(.space-x-3>:not(:last-child)){--tw-space-x-reverse:0;margin-inline-start:calc(calc(var(--spacing) * 3) * var(--tw-space-x-reverse));margin-inline-end:calc(calc(var(--spacing) * 3) * calc(1 - var(--tw-space-x-reverse)))}:where(.space-x-4>:not(:last-child)){--tw-space-x-reverse:0;margin-inline-start:calc(calc(var(--spacing) * 4) * var(--tw-space-x-reverse));margin-inline-end:calc(calc(var(--spacing) * 4) * calc(1 - var(--tw-space-x-reverse)))}:where(.space-x-6>:not(:last-child)){--tw-space-x-reverse:0;margin-inline-start:calc(calc(var(--spacing) * 6) * var(--tw-space-x-reverse));margin-inline-end:calc(calc(var(--spacing) * 6) * calc(1 - var(--tw-space-x-reverse)))}.overflow-hidden{overflow:hidden}.overflow-y-auto{overflow-y:auto}.rounded{border-radius:.25rem}.rounded-full{border-radius:3.40282e38px}.rounded-lg{border-radius:var(--radius-lg)}.rounded-md{border-radius:var(--radius-md)}.rounded-sm{border-radius:var(--radius-sm)}.rounded-xl{border-radius:var(--radius-xl)}.border{border-style:var(--tw-border-style);border-width:1px}.border-t{border-top-style:var(--tw-border-style);border-top-width:1px}.border-b{border-bottom-style:var(--tw-border-style);border-bottom-width:1px}.border-\[\#16a34a\]{border-color:#16a34a}.border-\[\#0070f3\]{border-color:#0070f3}.border-\[\#eaeaea\]{border-color:#eaeaea}.border-red-200{border-color:var(--color-red-200)}.border-red-600{border-color:var(--color-red-600)}.border-transparent{border-color:#0000}.bg-\[\#0070f3\]{background-color:#0070f3}.bg-\[\#eaeaea\]{background-color:#eaeaea}.bg-\[\#ebf5ff\]{background-color:#ebf5ff}.bg-\[\#f0fdf4\]{background-color:#f0fdf4}.bg-\[\#fafafa\]{background-color:#fafafa}.bg-\[\#fafafa\]\/80{background-color:oklab(98.5104% -1.19209e-7 5.96046e-8/.8)}.bg-black{background-color:var(--color-black)}.bg-red-50{background-color:var(--color-red-50)}.bg-white{background-color:var(--color-white)}.p-2{padding:calc(var(--spacing) * 2)}.p-3{padding:calc(var(--spacing) * 3)}.p-4{padding:calc(var(--spacing) * 4)}.p-6{padding:calc(var(--spacing) * 6)}.p-8{padding:calc(var(--spacing) * 8)}.px-2{padding-inline:calc(var(--spacing) * 2)}.px-2\.5{padding-inline:calc(var(--spacing) * 2.5)}.px-3{padding-inline:calc(var(--spacing) * 3)}.px-6{padding-inline:calc(var(--spacing) * 6)}.py-1{padding-block:calc(var(--spacing) * 1)}.py-1\.5{padding-block:calc(var(--spacing) * 1.5)}.py-2{padding-block:calc(var(--spacing) * 2)}.pt-2{padding-top:calc(var(--spacing) * 2)}.text-center{text-align:center}.text-left{text-align:left}.text-right{text-align:right}.font-mono{font-family:var(--font-mono)}.font-sans{font-family:var(--font-sans)}.text-sm{font-size:var(--text-sm);line-height:var(--tw-leading,var(--text-sm--line-height))}.text-xs{font-size:var(--text-xs);line-height:var(--tw-leading,var(--text-xs--line-height))}.text-\[10px\]{font-size:10px}.text-\[11px\]{font-size:11px}.text-\[12px\]{font-size:12px}.text-\[14px\]{font-size:14px}.text-\[20px\]{font-size:20px}.leading-relaxed{--tw-leading:var(--leading-relaxed);line-height:var(--leading-relaxed)}.font-medium{--tw-font-weight:var(--font-weight-medium);font-weight:var(--font-weight-medium)}.font-semibold{--tw-font-weight:var(--font-weight-semibold);font-weight:var(--font-weight-semibold)}.tracking-tight{--tw-tracking:var(--tracking-tight);letter-spacing:var(--tracking-tight)}.tracking-widest{--tw-tracking:var(--tracking-widest);letter-spacing:var(--tracking-widest)}.text-\[\#4d4d4d\]{color:#4d4d4d}.text-\[\#16a34a\]{color:#16a34a}.text-\[\#0052ad\]{color:#0052ad}.text-\[\#0070f3\]{color:#0070f3}.text-\[\#444\]{color:#444}.text-\[\#666\]{color:#666}.text-\[\#999\]{color:#999}.text-\[\#166534\]{color:#166534}.text-black{color:var(--color-black)}.text-red-500{color:var(--color-red-500)}.text-red-600{color:var(--color-red-600)}.text-red-700{color:var(--color-red-700)}.text-white{color:var(--color-white)}.uppercase{text-transform:uppercase}.antialiased{-webkit-font-smoothing:antialiased;-moz-osx-font-smoothing:grayscale}.opacity-40{opacity:.4}.opacity-70{opacity:.7}.shadow-\[0_1px_1px_rgba\(0\,0\,0\,0\.05\)\,0_8px_16px_-4px_rgba\(0\,0\,0\,0\.1\)\,0_24px_32px_-8px_rgba\(0\,0\,0\,0\.1\)\,inset_0_0_0_1px_\#ebebeb\]{--tw-shadow:0 1px 1px var(--tw-shadow-color,#0000000d), 0 8px 16px -4px var(--tw-shadow-color,#0000001a), 0 24px 32px -8px var(--tw-shadow-color,#0000001a), inset 0 0 0 1px var(--tw-shadow-color,#ebebeb);box-shadow:var(--tw-inset-shadow), var(--tw-inset-ring-shadow), var(--tw-ring-offset-shadow), var(--tw-ring-shadow), var(--tw-shadow)}.shadow-\[0_2px_4px_0_rgba\(0\,0\,0\,0\.02\)\]{--tw-shadow:0 2px 4px 0 var(--tw-shadow-color,#00000005);box-shadow:var(--tw-inset-shadow), var(--tw-inset-ring-shadow), var(--tw-ring-offset-shadow), var(--tw-ring-shadow), var(--tw-shadow)}.shadow-\[0_4px_14px_0_rgba\(0\,0\,0\,0\.1\)\]{--tw-shadow:0 4px 14px 0 var(--tw-shadow-color,#0000001a);box-shadow:var(--tw-inset-shadow), var(--tw-inset-ring-shadow), var(--tw-ring-offset-shadow), var(--tw-ring-shadow), var(--tw-shadow)}.shadow-sm{--tw-shadow:0 1px 3px 0 var(--tw-shadow-color,#0000001a), 0 1px 2px -1px var(--tw-shadow-color,#0000001a);box-shadow:var(--tw-inset-shadow), var(--tw-inset-ring-shadow), var(--tw-ring-offset-shadow), var(--tw-ring-shadow), var(--tw-shadow)}.backdrop-blur-sm{--tw-backdrop-blur:blur(var(--blur-sm));-webkit-backdrop-filter:var(--tw-backdrop-blur,) var(--tw-backdrop-brightness,) var(--tw-backdrop-contrast,) var(--tw-backdrop-grayscale,) var(--tw-backdrop-hue-rotate,) var(--tw-backdrop-invert,) var(--tw-backdrop-opacity,) var(--tw-backdrop-saturate,) var(--tw-backdrop-sepia,);backdrop-filter:var(--tw-backdrop-blur,) var(--tw-backdrop-brightness,) var(--tw-backdrop-contrast,) var(--tw-backdrop-grayscale,) var(--tw-backdrop-hue-rotate,) var(--tw-backdrop-invert,) var(--tw-backdrop-opacity,) var(--tw-backdrop-saturate,) var(--tw-backdrop-sepia,)}.transition{transition-property:color,background-color,border-color,outline-color,text-decoration-color,fill,stroke,--tw-gradient-from,--tw-gradient-via,--tw-gradient-to,opacity,box-shadow,transform,translate,scale,rotate,filter,-webkit-backdrop-filter,backdrop-filter,display,content-visibility,overlay,pointer-events;transition-timing-function:var(--tw-ease,var(--default-transition-timing-function));transition-duration:var(--tw-duration,var(--default-transition-duration))}.transition-all{transition-property:all;transition-timing-function:var(--tw-ease,var(--default-transition-timing-function));transition-duration:var(--tw-duration,var(--default-transition-duration))}.transition-colors{transition-property:color,background-color,border-color,outline-color,text-decoration-color,fill,stroke,--tw-gradient-from,--tw-gradient-via,--tw-gradient-to;transition-timing-function:var(--tw-ease,var(--default-transition-timing-function));transition-duration:var(--tw-duration,var(--default-transition-duration))}.ease-in-out{--tw-ease:var(--ease-in-out);transition-timing-function:var(--ease-in-out)}.outline-none{--tw-outline-style:none;outline-style:none}@media (hover:hover){.hover\:border-red-600:hover{border-color:var(--color-red-600)}.hover\:bg-\[\#333\]:hover{background-color:#333}.hover\:bg-\[\#fafafa\]:hover{background-color:#fafafa}.hover\:bg-red-50:hover{background-color:var(--color-red-50)}.hover\:text-black:hover{color:var(--color-black)}}.focus\:border-black:focus{border-color:var(--color-black)}.focus\:ring-black:focus{--tw-ring-color:var(--color-black)}.disabled\:opacity-50:disabled{opacity:.5}@media (min-width:48rem){.md\:w-80{width:calc(var(--spacing) * 80)}.md\:flex-row{flex-direction:row}}}@property --tw-rotate-x{syntax:"*";inherits:false}@property --tw-rotate-y{syntax:"*";inherits:false}@property --tw-rotate-z{syntax:"*";inherits:false}@property --tw-skew-x{syntax:"*";inherits:false}@property --tw-skew-y{syntax:"*";inherits:false}@property --tw-space-y-reverse{syntax:"*";inherits:false;initial-value:0}@property --tw-space-x-reverse{syntax:"*";inherits:false;initial-value:0}@property --tw-border-style{syntax:"*";inherits:false;initial-value:solid}@property --tw-leading{syntax:"*";inherits:false}@property --tw-font-weight{syntax:"*";inherits:false}@property --tw-tracking{syntax:"*";inherits:false}@property --tw-shadow{syntax:"*";inherits:false;initial-value:0 0 #0000}@property --tw-shadow-color{syntax:"*";inherits:false}@property --tw-shadow-alpha{syntax:"<percentage>";inherits:false;initial-value:100%}@property --tw-inset-shadow{syntax:"*";inherits:false;initial-value:0 0 #0000}@property --tw-inset-shadow-color{syntax:"*";inherits:false}@property --tw-inset-shadow-alpha{syntax:"<percentage>";inherits:false;initial-value:100%}@property --tw-ring-color{syntax:"*";inherits:false}@property --tw-ring-shadow{syntax:"*";inherits:false;initial-value:0 0 #0000}@property --tw-inset-ring-color{syntax:"*";inherits:false}@property --tw-inset-ring-shadow{syntax:"*";inherits:false;initial-value:0 0 #0000}@property --tw-ring-inset{syntax:"*";inherits:false}@property --tw-ring-offset-width{syntax:"<length>";inherits:false;initial-value:0}@property --tw-ring-offset-color{syntax:"*";inherits:false;initial-value:#fff}@property --tw-ring-offset-shadow{syntax:"*";inherits:false;initial-value:0 0 #0000}@property --tw-backdrop-blur{syntax:"*";inherits:false}@property --tw-backdrop-brightness{syntax:"*";inherits:false}@property --tw-backdrop-contrast{syntax:"*";inherits:false}@property --tw-backdrop-grayscale{syntax:"*";inherits:false}@property --tw-backdrop-hue-rotate{syntax:"*";inherits:false}@property --tw-backdrop-invert{syntax:"*";inherits:false}@property --tw-backdrop-opacity{syntax:"*";inherits:false}@property --tw-backdrop-saturate{syntax:"*";inherits:false}@property --tw-backdrop-sepia{syntax:"*";inherits:false}@property --tw-ease{syntax:"*";inherits:false}@keyframes spin{to{transform:rotate(360deg)}}@keyframes pulse{50%{opacity:.5}}
@keyframes slide { 0% { transform: translateX(-100%); } 100% { transform: translateX(300%); } }
@keyframes spin { from { transform: rotate(0deg); } to { transform: rotate(360deg); } }</style>
</head>
<body class="flex flex-col h-screen w-full bg-[#fafafa] font-sans text-black overflow-hidden">
  
  <header class="flex items-center justify-between h-14 px-6 bg-white border-b border-[#eaeaea] shrink-0">
    <div class="flex items-center space-x-3">
      <span class="font-semibold tracking-tight text-sm uppercase">HiTECH R4 Wifi Manager</span>
    </div>
    <div class="flex items-center space-x-2">
      <div id="status-dot" class="w-2 h-2 rounded-full bg-[#0070f3] animate-pulse"></div>
      <span id="status-text" class="text-[12px] font-medium text-[#666] uppercase">SYS_STATUS: CONNECTING</span>
    </div>
  </header>

  <main class="flex-1 flex flex-col md:flex-row gap-6 p-6 overflow-hidden">
    
    <div class="flex-1 flex flex-col gap-6 overflow-hidden">
      <section class="bg-white rounded-lg border border-[#eaeaea] shadow-sm flex flex-col min-h-0 overflow-hidden relative">
        <div id="scan-progress" class="absolute inset-x-0 top-0 h-0.5 bg-[#eaeaea] overflow-hidden z-10 hidden">
          <div class="w-1/3 h-full bg-black animate-[slide_1s_ease-in-out_infinite]"></div>
        </div>
        
        <div class="p-4 border-b border-[#eaeaea] flex items-center justify-between bg-white z-0 relative">
          <div>
            <h2 class="text-sm font-semibold">Available Networks</h2>
            <p class="text-xs text-[#666]">Nearby wireless access points</p>
          </div>
          <button id="btn-scan" class="px-3 py-1.5 text-xs font-medium border border-[#eaeaea] rounded hover:bg-[#fafafa] transition-colors bg-white flex items-center gap-1.5 disabled:opacity-50">
            <svg id="icon-search" class="w-3 h-3" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" viewBox="0 0 24 24"><path d="M11.965 10.105v4L13.5 12.5a5 5 0 0 1 8 1.5" /><path d="M11.965 14.105h4" /><path d="M17.965 18.105h4L20.43 19.71a5 5 0 0 1-8-1.5" /><path d="M2 8.82a15 15 0 0 1 20 0" /><path d="M21.965 22.105v-4" /><path d="M5 12.86a10 10 0 0 1 3-2.032" /><path d="M8.5 16.429h.01" /></svg>
            <span id="txt-scan">Scan Now</span>
          </button>
        </div>

        <div class="flex-1 overflow-hidden p-2 z-0">
          <div id="networks-list" class="space-y-1 overflow-y-auto max-h-full h-full">
            <div class="p-4 text-center text-sm text-[#666]">No networks found. Try scanning.</div>
          </div>
        </div>
      </section>
    </div>

    <div class="w-full md:w-80 flex flex-col gap-6 overflow-y-auto shrink-0">
      <section class="bg-white rounded-lg border border-[#eaeaea] shadow-sm p-6 shrink-0">
        <div class="flex items-center gap-2 mb-6">
          <svg class="w-3.5 h-3.5 text-[#666]" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24"><path stroke-linecap="round" stroke-linejoin="round" d="M10.325 4.317c.426-1.756 2.924-1.756 3.35 0a1.724 1.724 0 002.573 1.066c1.543-.94 3.31.826 2.37 2.37a1.724 1.724 0 001.065 2.572c1.756.426 1.756 2.924 0 3.35a1.724 1.724 0 00-1.066 2.573c.94 1.543-.826 3.31-2.37 2.37a1.724 1.724 0 00-2.572 1.065c-.426 1.756-2.924 1.756-3.35 0a1.724 1.724 0 00-2.573-1.066c-1.543.94-3.31-.826-2.37-2.37a1.724 1.724 0 00-1.065-2.572c-1.756-.426-1.756-2.924 0-3.35a1.724 1.724 0 001.066-2.573c-.94-1.543.826-3.31 2.37-2.37.996.608 2.296.07 2.572-1.065z"></path><path stroke-linecap="round" stroke-linejoin="round" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z"></path></svg>
          <h2 class="text-[10px] font-medium text-[#666] uppercase tracking-widest">Configuration</h2>
        </div>
        
        <form id="config-form" class="space-y-4">
          <div id="error-box" class="hidden p-3 rounded bg-red-50 border border-red-200 text-red-700 text-xs font-medium"></div>

          <div class="space-y-1.5">
            <label class="text-[12px] font-medium text-[#444]">Network SSID</label>
            <input id="input-ssid" type="text" class="w-full px-3 py-2 text-sm bg-white border border-[#eaeaea] rounded outline-none focus:border-black transition-colors" placeholder="Enter SSID or select from list" required />
          </div>
          
          <div id="password-container" class="space-y-1.5 mt-1 hidden">
            <label class="text-[12px] font-medium text-[#444]">Password</label>
            <div class="relative">
              <input id="input-password" type="password" class="w-full px-3 py-2 text-sm bg-white border border-[#eaeaea] rounded outline-none focus:border-black transition-colors" placeholder="••••••••" />
              <button type="button" id="btn-toggle-pw" class="absolute right-3 top-2.5 text-[#999] hover:text-black transition-colors">
                <svg id="icon-eye" class="w-4 h-4" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24"><path d="M15 12a3 3 0 11-6 0 3 3 0 016 0z"/><path d="M2.458 12C3.732 7.943 7.523 5 12 5c4.478 0 8.268 2.943 9.542 7-1.274 4.057-5.064 7-9.542 7-4.477 0-8.268-2.943-9.542-7z"/></svg>
              </button>
            </div>
          </div>

          <div class="pt-2">
            <label class="flex items-center space-x-2 cursor-pointer">
              <input type="checkbox" id="input-static-ip" class="w-3.5 h-3.5 border border-[#eaeaea] rounded text-black focus:ring-black">
              <span class="text-[12px] font-medium text-[#444]">Use Static IP</span>
            </label>
          </div>

          <div id="static-ip-container" class="hidden space-y-3 p-3 bg-[#fafafa] border border-[#eaeaea] rounded">
            <div class="space-y-1">
              <label class="text-[11px] font-medium text-[#666]">IP Address</label>
              <input id="input-ip" type="text" pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$" class="w-full px-2.5 py-1.5 text-xs bg-white border border-[#eaeaea] rounded outline-none focus:border-black transition-colors" placeholder="192.168.1.50" />
            </div>
            <div class="space-y-1">
              <label class="text-[11px] font-medium text-[#666]">Gateway</label>
              <input id="input-gw" type="text" pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$" class="w-full px-2.5 py-1.5 text-xs bg-white border border-[#eaeaea] rounded outline-none focus:border-black transition-colors" placeholder="192.168.1.1" />
            </div>
            <div class="space-y-1">
              <label class="text-[11px] font-medium text-[#666]">Subnet Mask</label>
              <input id="input-sn" type="text" pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$" class="w-full px-2.5 py-1.5 text-xs bg-white border border-[#eaeaea] rounded outline-none focus:border-black transition-colors" placeholder="255.255.255.0" />
            </div>
            <div class="space-y-1">
              <label class="text-[11px] font-medium text-[#666]">DNS Server</label>
              <input id="input-dns" type="text" pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$" class="w-full px-2.5 py-1.5 text-xs bg-white border border-[#eaeaea] rounded outline-none focus:border-black transition-colors" placeholder="8.8.8.8" />
            </div>
          </div>

          <div id="custom-params-container" class="space-y-3"></div>

          <button id="btn-connect" type="submit" disabled class="w-full py-2 bg-black text-white text-sm font-medium rounded hover:bg-[#333] transition-all shadow-[0_4px_14px_0_rgba(0,0,0,0.1)] mt-4 disabled:opacity-50 flex items-center justify-center gap-2">
            <span id="txt-connect">Connect Device</span>
          </button>
        </form>

        <button id="btn-reset" type="button" class="hidden w-full py-2 bg-white text-red-600 border border-red-200 text-sm font-medium rounded hover:bg-red-50 hover:border-red-600 transition-all shadow-[0_2px_4px_0_rgba(0,0,0,0.02)] mt-4 items-center justify-center gap-2">
          <span id="txt-reset">Reset Configuration</span>
        </button>
      </section>

      <div id="status-alert-box" class="p-4 rounded-lg bg-[#ebf5ff] border border-[#0070f3] border-opacity-20 shrink-0">
        <div class="flex items-start space-x-3">
          <svg id="status-alert-icon" class="w-5 h-5 text-[#0070f3] mt-0.5 shrink-0" fill="currentColor" viewBox="0 0 20 20"><path fill-rule="evenodd" d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-7-4a1 1 0 11-2 0 1 1 0 012 0zM9 9a1 1 0 000 2v3a1 1 0 001 1h1a1 1 0 100-2v-3a1 1 0 00-1-1H9z" clip-rule="evenodd"></path></svg>
          <p id="status-alert-text" class="text-xs text-[#0052ad] leading-relaxed">
            After connecting, this device will switch to client mode. You may need to refresh your local network view to find its new IP.
          </p>
        </div>
      </div>
    </div>
  </main>

  <footer class="h-10 px-6 border-t border-[#eaeaea] bg-white flex items-center justify-between text-[10px] text-[#666] font-medium uppercase tracking-widest shrink-0">
    <span id="footer-info-fw">2026.6.14</span>
    <div class="flex items-center space-x-6">
      <div class="flex items-center space-x-1.5"><svg class="w-3.5 h-3.5" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect width="18" height="18" x="3" y="3" rx="2" /><path d="M11 9h4a2 2 0 0 0 2-2V3" /><circle cx="9" cy="9" r="2" /><path d="M7 21v-4a2 2 0 0 1 2-2h4" /><circle cx="15" cy="15" r="2" /></svg><span id="footer-info-board">-</span></div>
      <div class="flex items-center space-x-1.5"><svg class="w-3.5 h-3.5" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M12 20v2" /><path d="M12 2v2" /><path d="M17 20v2" /><path d="M17 2v2" /><path d="M2 12h2" /><path d="M2 17h2" /><path d="M2 7h2" /><path d="M20 12h2" /><path d="M20 17h2" /><path d="M20 7h2" /><path d="M7 20v2" /><path d="M7 2v2" /><rect x="4" y="4" width="16" height="16" rx="2" /><rect x="8" y="8" width="8" height="8" rx="1" /></svg><span id="footer-info-cpu">-</span></div>
      <div class="flex items-center space-x-1.5"><svg class="w-3.5 h-3.5" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M12 12v-2" /><path d="M12 18v-2" /><path d="M16 12v-2" /><path d="M16 18v-2" /><path d="M2 11h1.5" /><path d="M20 18v-2" /><path d="M20.5 11H22" /><path d="M4 18v-2" /><path d="M8 12v-2" /><path d="M8 18v-2" /><rect x="2" y="6" width="20" height="10" rx="2" /></svg><span id="footer-info-ram">-</span></div>
    </div>
  </footer>



  <script>
    const $ = id => document.getElementById(id);
    let currentNetworks = [];
    let selectedSsid = '';
    let customParamFields = [];
    
    async function init() {
      try {
        const res = await fetch('/api/status');
        const data = await res.json();
        $('status-text').innerText = 'SYS_STATUS: ' + data.status;
        if (data.status === 'AP_MODE') {
           scanNetworks();
        } else {
           $('status-dot').classList.remove('animate-pulse');
           $('btn-reset').classList.remove('hidden');
           $('btn-reset').classList.add('flex');
        }
        
        fetch('/api/info')
          .then(r => r.json())
          .then(info => {
            $('footer-info-board').innerText = info.board || '-';
            $('footer-info-cpu').innerText = info.cpu || '-';
            $('footer-info-ram').innerText = info.ram || '-';
          }).catch(e => e);

        fetch('/api/params')
          .then(r => r.json())
          .then(params => {
             if(Array.isArray(params) && params.length > 0) {
               customParamFields = params.map(p => p.id);
               const html = params.map(p => 
                 '<div class="space-y-1.5 pt-2 border-t border-[#eaeaea] mt-2">' +
                   '<label class="text-[12px] font-medium text-[#444]">' + p.label + '</label>' +
                   '<input id="custom-' + p.id + '" type="text" class="w-full px-3 py-2 text-sm bg-white border border-[#eaeaea] rounded outline-none focus:border-black transition-colors" value="' + p.value + '" />' +
                 '</div>'
               ).join('');
               $('custom-params-container').innerHTML = html;
             }
          }).catch(e => e);

      } catch(e) {}
    }

    async function scanNetworks() {
      $('scan-progress').classList.remove('hidden');
      $('btn-scan').disabled = true;
      $('icon-search').innerHTML = '<path d="M21 12a9 9 0 1 1-6.219-8.56" />';
      $('icon-search').classList.add('animate-spin');
      $('txt-scan').innerText = 'Scanning';
      $('networks-list').innerHTML = '<div class="p-4 text-center text-sm text-[#666]">Scanning for networks...</div>';
      
      try {
        const res = await fetch('/api/scan');
        const data = await res.json();
        currentNetworks = data;
        renderNetworks();
      } catch(e) {
        $('networks-list').innerHTML = '<div class="p-4 text-center text-sm text-red-700">Failed to scan networks</div>';
      } finally {
        $('scan-progress').classList.add('hidden');
        $('btn-scan').disabled = false;
        $('icon-search').innerHTML = '<path d="M11.965 10.105v4L13.5 12.5a5 5 0 0 1 8 1.5" /><path d="M11.965 14.105h4" /><path d="M17.965 18.105h4L20.43 19.71a5 5 0 0 1-8-1.5" /><path d="M2 8.82a15 15 0 0 1 20 0" /><path d="M21.965 22.105v-4" /><path d="M5 12.86a10 10 0 0 1 3-2.032" /><path d="M8.5 16.429h.01" />';
        $('icon-search').classList.remove('animate-spin');
        $('txt-scan').innerText = 'Scan Now';
      }
    }

    function getWifiIconStr(rssi) {
       let path = '';
       if (rssi <= -90) path = '<path d="M12 20h.01" />';
       else if (rssi <= -80) path = '<path d="M12 20h.01" /><path d="M8.5 16.429a5 5 0 0 1 7 0" />';
       else if (rssi <= -67) path = '<path d="M12 20h.01" /><path d="M5 12.859a10 10 0 0 1 14 0" /><path d="M8.5 16.429a5 5 0 0 1 7 0" />';
       else path = '<path d="M12 20h.01" /><path d="M2 8.82a15 15 0 0 1 20 0" /><path d="M5 12.859a10 10 0 0 1 14 0" /><path d="M8.5 16.429a5 5 0 0 1 7 0" />';
       return '<svg class="w-4 h-4 text-black shrink-0" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" viewBox="0 0 24 24">' + path + '</svg>';
    }

    function renderNetworks() {
      const list = $('networks-list');
      if(currentNetworks.length === 0) {
        list.innerHTML = '<div class="p-4 text-center text-sm text-[#666]">No networks found.</div>';
        return;
      }
      
      list.innerHTML = currentNetworks.map(net => {
        const isEnc = net.encryption !== 'NONE';
        const isSelected = selectedSsid === net.ssid;
        const bgClass = isSelected ? 'bg-[#fafafa] border-[#0070f3]' : 'border-transparent hover:bg-[#fafafa]';
        
        return '<button type="button" onclick="selectNetwork(\'' + net.ssid + '\', ' + isEnc + ')" class="w-full flex items-center justify-between p-3 rounded-md transition-colors text-left border ' + bgClass + '">' +
            '<div class="flex items-center gap-3">' +
              getWifiIconStr(net.rssi) +
              '<span class="text-sm">' + net.ssid + '</span>' +
            '</div>' +
            '<div class="flex items-center space-x-4">' +
              '<div class="flex items-center space-x-2">' +
                 '<span class="text-[11px] font-mono text-[#666]">' + net.encryption + '</span>' +
                 '<span class="text-[11px] font-mono text-[#666]">' + net.rssi + ' dBm</span>' +
              '</div>' +
              (isEnc ? '<svg class="w-3.5 h-3.5 text-[#666]" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24"><path d="M12 15v2m-6 4h12a2 2 0 002-2v-6a2 2 0 00-2-2H6a2 2 0 00-2 2v6a2 2 0 002 2zm10-10V7a4 4 0 00-8 0v4h8z"/></svg>' : '<div class="w-3.5 h-3.5"></div>') +
            '</div>' +
          '</button>';
      }).join('');
    }

    window.selectNetwork = function(ssid, isEnc) {
      selectedSsid = ssid;
      $('input-ssid').value = ssid;
      $('btn-connect').disabled = false;
      if(isEnc) {
        $('password-container').classList.remove('hidden');
        $('input-password').required = true;
      } else {
        $('password-container').classList.add('hidden');
        $('input-password').required = false;
        $('input-password').value = '';
      }
      renderNetworks();
    };

    $('input-ssid').addEventListener('input', (e) => {
      selectedSsid = e.target.value;
      $('btn-connect').disabled = !selectedSsid;
      $('password-container').classList.remove('hidden');
      $('input-password').required = true;
      renderNetworks();
    });

    $('btn-scan').addEventListener('click', scanNetworks);
    
    let pwVisible = false;
    $('btn-toggle-pw').addEventListener('click', () => {
       pwVisible = !pwVisible;
       $('input-password').type = pwVisible ? 'text' : 'password';
       $('icon-eye').innerHTML = pwVisible 
          ? '<path stroke-linecap="round" stroke-linejoin="round" d="M13.875 18.825A10.05 10.05 0 0112 19c-4.478 0-8.268-2.943-9.543-7a9.97 9.97 0 011.563-3.029m5.858.908a3 3 0 114.243 4.243M9.878 9.878l4.242 4.242M9.88 9.88l-3.29-3.29m7.532 7.532l3.29 3.29M3 3l3.59 3.59m0 0A9.953 9.953 0 0112 5c4.478 0 8.268 2.943 9.543 7a10.025 10.025 0 01-4.132 5.411m0 0L21 21" />'
          : '<path stroke-linecap="round" stroke-linejoin="round" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z"/><path stroke-linecap="round" stroke-linejoin="round" d="M2.458 12C3.732 7.943 7.523 5 12 5c4.478 0 8.268 2.943 9.542 7-1.274 4.057-5.064 7-9.542 7-4.477 0-8.268-2.943-9.542-7z"/>';
    });

    $('input-static-ip').addEventListener('change', (e) => {
       const checked = e.target.checked;
       if (checked) {
          $('static-ip-container').classList.remove('hidden');
          $('input-ip').required = true;
          $('input-gw').required = true;
          $('input-sn').required = true;
          $('input-dns').required = true;
       } else {
          $('static-ip-container').classList.add('hidden');
          $('input-ip').required = false;
          $('input-gw').required = false;
          $('input-sn').required = false;
          $('input-dns').required = false;
       }
    });

    $('config-form').addEventListener('submit', async (e) => {
       e.preventDefault();
       $('btn-connect').disabled = true;
       $('txt-connect').innerText = 'Connecting...';
       $('error-box').classList.add('hidden');
       
       try {
         const formData = new URLSearchParams();
         formData.append('ssid', selectedSsid);
         formData.append('password', $('input-password').value);
         
         const isStatic = $('input-static-ip').checked;
         formData.append('useStatic', isStatic ? 'true' : 'false');
         if (isStatic) {
           formData.append('ip', $('input-ip').value);
           formData.append('gw', $('input-gw').value);
           formData.append('sn', $('input-sn').value);
           formData.append('dns', $('input-dns').value);
         }

         customParamFields.forEach(id => {
           formData.append(id, $('custom-' + id).value);
         });
         
         const res = await fetch('/api/connect', {
           method: 'POST',
           body: formData
         });
         
         if(res.ok) {
           const json = await res.json();
           if(json.status === 'error') {
             $('error-box').innerText = json.message || 'Connection failed';
             $('error-box').classList.remove('hidden');
           } else {
             $('status-alert-box').className = 'p-4 rounded-lg bg-[#f0fdf4] border border-[#16a34a] border-opacity-20 shrink-0';
             $('status-alert-icon').outerHTML = '<svg id="status-alert-icon" class="w-5 h-5 text-[#16a34a] mt-0.5 shrink-0" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" viewBox="0 0 24 24"><path d="M15.2 3a2 2 0 0 1 1.4.6l3.8 3.8a2 2 0 0 1 .6 1.4V19a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2z" /><path d="M17 21v-7a1 1 0 0 0-1-1H8a1 1 0 0 0-1 1v7" /><path d="M7 3v4a1 1 0 0 0 1 1h7" /></svg>';
             $('status-alert-text').className = 'text-xs text-[#166534] leading-relaxed';
             $('status-alert-text').innerText = 'Configuration saved successfully. The device is now rebooting into Client Mode. Please reconnect your network.';
           }
         } else {
           $('error-box').innerText = 'Server error occurred.';
           $('error-box').classList.remove('hidden');
         }
       } catch(e) {
         $('error-box').innerText = 'Network error occurred.';
         $('error-box').classList.remove('hidden');
       } finally {
         $('btn-connect').disabled = false;
         $('txt-connect').innerText = 'Connect Device';
       }
    });

    $('btn-reset').addEventListener('click', async () => {
       $('btn-reset').disabled = true;
       $('txt-reset').innerText = 'Resetting...';
       try {
         const res = await fetch('/api/reset', { method: 'POST' });
         if (res.ok) {
           $('status-alert-box').className = 'p-4 rounded-lg bg-[#f0fdf4] border border-[#16a34a] border-opacity-20 shrink-0';
           $('status-alert-icon').outerHTML = '<svg id="status-alert-icon" class="w-5 h-5 text-[#16a34a] mt-0.5 shrink-0" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" viewBox="0 0 24 24"><path d="M15.2 3a2 2 0 0 1 1.4.6l3.8 3.8a2 2 0 0 1 .6 1.4V19a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2z" /><path d="M17 21v-7a1 1 0 0 0-1-1H8a1 1 0 0 0-1 1v7" /><path d="M7 3v4a1 1 0 0 0 1 1h7" /></svg>';
           $('status-alert-text').className = 'text-xs text-[#166534] leading-relaxed';
           $('status-alert-text').innerText = 'The device configuration has been reset. It is now rebooting into AP Mode.';
         }
       } catch(e) {
         $('btn-reset').disabled = false;
         $('txt-reset').innerText = 'Reset Configuration';
       }
    });

    init();
  </script>
</body>
</html>
)=====";

#endif